#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <signal.h>

#define SERVER_FIFO "server_fifo"
#define CLIENT_FIFO "client_fifo%d"

struct lembrete{
	pid_t pid;
	int tempo;
	char texto[50];
};

struct tdados{
	struct lembrete *tArray;
	pthread_mutex_t *lock;
	int nLembretesMax;
	char comando[10];
};

struct lembretes *array;
int countLembretes;

void insere(struct lembrete **lembretes, struct lembrete array){}
bool consulta(struct lembrete *lembretes, pid_t pid){return true;}
void remover(struct lembrete **lembretes, pid_t pid){}

void *routineReceber(void *arg){
	struct tdados *t = (struct tdados *) arg;
	struct lembrete lem;
	char buffer[25];

	int fd_server = open(SERVER_FIFO, O_RDONLY | O_NONBLOCK);
	read(fd_server, &lem, sizeof(lem));

	char client_fifo_name[15];
	sprintf(client_fifo_name, CLIENT_FIFO, lem.pid);

	int fd_client = open(client_fifo_name, O_WRONLY | O_NONBLOCK);

	pthread_mutex_lock(t->lock);
	if(strcmp(t->comando, "lembrete") == 0){
		if(countLembretes <= t->nLembretesMax){
			insere(&t->tArray, lem);
			countLembretes++;
			write(fd_client, "INSUCESSO", sizeof(7));
		} else{
			write(fd_client, "INSUCESSO", sizeof(9));
		}
	} else if(strcmp(t->comando, "agenda") == 0){
		for(int i = 0; i < countLembretes; i++){
			if(lem.pid == t->tArray[i].pid){
				printf("%d | %d | %s", t->tArray[i].pid, t->tArray[i].tempo, t->tArray[i].texto);
				write(fd_client, &t->tArray[i], sizeof(t->tArray[i]));
			}
		}
	} else if(strcmp(t->comando, "termina") == 0){
		for(int i = 0; i < countLembretes; i++){
			if(consulta(&t->tArray[i], lem.pid) == true){
				remover(&t->tArray, lem.pid);
				countLembretes--;
				i--;
			}
		}
	}
	pthread_mutex_unlock(t->lock);

	close(fd_client);
	close(fd_server);
}

void *routineTimer(void *arg){
	struct tdados *t = (struct tdados *) arg;

	while (1) {
        	pthread_mutex_lock(t->lock);
        	for (int i = 0; i < countLembretes; i++) {
            		if (t->tArray[i].tempo > 0) {
                		t->tArray[i].tempo--;
            		} else {
                      		char client_fifo_name[15];
                		sprintf(client_fifo_name, CLIENT_FIFO, t->tArray[i].pid);

                		int fd_client = open(client_fifo_name, O_WRONLY | O_NONBLOCK);
              			write(fd_client, t->tArray[i].texto, sizeof(t->tArray[i].texto));
                    		close(fd_client);
                	}

                	remover(&t->tArray, t->tArray[i].pid);
                	countLembretes--;
                	i--;
        	}
		pthread_mutex_unlock(t->lock);
       	}

        sleep(1);
}

void handler_signal(int sig){
	if(sig == SIGINT){
		printf("SIGINT recebido!");
	} else if(sig == SIGALRM){
		printf("SIGALRM recebido, time over!");
	}

	unlink(SERVER_FIFO);
	free(array);
	exit(0);
}

int main(int argc, char **argv){
	struct lembrete array[atoi(getenv("NMAX"))];
	struct tdados tdata;
	pthread_t threads[2];
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL);

	tdata.lock = &mutex;
	tdata.tArray = array;
	tdata.nLembretesMax = atoi(getenv("NMAX"));

	mkfifo(SERVER_FIFO, 0777);

	pthread_create(&threads[0], NULL, &routineReceber, &tdata);
	pthread_create(&threads[1], NULL, &routineTimer, &tdata);

	while(1){ }

	for(int i = 0; i < 2; i++){
                pthread_join(threads[i], NULL);
        }

	pthread_mutex_destroy(&mutex);
}

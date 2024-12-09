#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CLIENT_FIFO "sensor_fifo%d"

struct sensor{
	int pid;
	int valor;
	char nome[10];
};

struct tdados{
	struct sensor *tArray;
	struct sensor *tArraySensores;
	int flag;
	pthread_mutex_t *lock;
};

struct sensor arraySensores[10];
struct sensor arrayMedicoes[1000];
int nMedicoes = 0, nSensores = 0;

void *routineInicial(void *arg){
	struct tdados *t = (struct tdados *) arg;
	struct sensor sen;

	while(!t->flag && nSensores <= 10){
		int fd_server = open(getenv("NPBACKEND"), O_RDONLY);
		read(fd_server, &sen, sizeof(sen));
		close(fd_server);
		t->tArraySensores[nSensores++] = sen;
	}

	if(nSensores == 10){
		for(int i = 0; i < 10; i++){
			char fifo_client[20];
			sprintf(fifo_client, CLIENT_FIFO, t->tArray[i].pid);
                	int fd_client = open(fifo_client, O_WRONLY);
                	write(fd_client, "a receber informação", sizeof(20));

                	close(fd_client);
		}
	}
}

void *routineReceber(void *arg){
	struct tdados *t = (struct tdados *) arg;
	struct sensor sen;

	while(!t->flag){
		int fd_server = open(getenv("NPBACKEND"), O_RDONLY);
                read(fd_server, &sen, sizeof(sen));

		if(nSensores == 10){
			pthread_mutex_lock(t->lock);
			if(nMedicoes < 1000){
				t->tArray[nMedicoes++] = sen;
			} else {
				nMedicoes = 0;
				t->tArray[nMedicoes++] = sen;
			}
			pthread_mutex_unlock(t->lock);

			printf("%d &s %d\n", sen.pid, sen.nome, sen.valor);
			fflush(stdout);
		}

		close(fd_server);
	}
}

int main(int argc, char **argv){
	if(getenv("NPBACKEND") != NULL){
		mkfifo(getenv("NPBACKEND"), 0777);
	}

	char comando[20];

	pthread_mutex_t mutex;
	pthread_t threads[2];

	pthread_mutex_init(&mutex, NULL);

	struct tdados tdata;
	tdata.tArray = arrayMedicoes;
	tdata.tArraySensores = arraySensores;
	tdata.lock = &mutex;
	tdata.flag = 0;

	pthread_create(&threads[0], NULL, &routineInicial, &tdata);
	pthread_create(&threads[1], NULL, &routineReceber, &tdata);

	while(strcmp(comando, "encerra") != 0){
		scanf("%s", comando);

		if (strncmp(comando, "ver ", 4) == 0) {
			char nome[10];
            		sscanf(comando + 8, "%s", nome);

            		pthread_mutex_lock(&mutex);
            		for (int i = nMedicoes; i > 0; i--){
               			if (strcmp(tdata.tArray[i].nome, nome) == 0){
                    			printf("%d %s %d\n", tdata.tArray[i].pid, tdata.tArray[i].nome, tdata.tArray[i].valor);
                    			break;
                		}
            		}
            		pthread_mutex_unlock(&mutex);
        	} else if(strcmp(comando, "consulta") == 0){
			for(int i = 0; i < nMedicoes; i++){
				printf("%d %s %d\n", arrayMedicoes[i].pid, arrayMedicoes[i].nome, arrayMedicoes[i].valor);
			}
		}
	}

	for(int i = 0; i < nSensores; i++){
                char fifo_client[20];
                sprintf(fifo_client, CLIENT_FIFO, tdata.tArraySensores[i].pid);
                int fd_client = open(fifo_client, O_WRONLY);
                write(fd_client, "encerrou", sizeof(8));
                close(fd_client);
		printf("%d %s %d\n", arraySensores[i].pid, arraySensores[i].nome, arraySensores[i].valor);
	}

	for(int i = 0; i < 2; i++){
		tdata.flag = 1;
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	unlink(getenv("NPBACKEND"));

	return 0;
}

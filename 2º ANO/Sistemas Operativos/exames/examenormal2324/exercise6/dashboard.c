#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int count = 0;

struct tdata{
	int pid;
	int flag;
	char arg[10];
	char nome[10];
	int fd_fifo;
	int temporizador;
	pthread_mutex_t *lock;
};

void *routine(void *arg){
	struct tdata *t = (struct tdata *) arg;

	int FDPF[2], FDPFF[2], status;
	char buffer[15];

	while(!t->flag){
		if(pipe(FDPF) == -1){
			printf("[error] creating pipe\n");
			return 0;
		}

		if(pipe(FDPFF) == -1){
                	printf("[error] creating pipe\n");
                	return 0;
        	}

		t->pid = fork();
		if(t->pid < 0){
			printf("[error]\n");
		} else if(t->pid == 0){
			close(STDIN_FILENO);
			close(FDPF[1]);
			dup(FDPF[0]);
			close(FDPF[0]);

			close(STDOUT_FILENO);
                	close(FDPFF[0]);
                	dup(FDPFF[1]);
                	close(FDPFF[1]);

			execlp(t->nome, t->nome, NULL);
		} else if(t->pid > 0){
			close(FDPF[0]);
			int writePipe = write(FDPF[1], t->arg, sizeof(t->arg));
			if(writePipe == -1){
				printf("[ERROR] writiing pipe\n");
				return 0;
			}
			close(FDPF[1]);
			close(FDPFF[1]);
			int readPipe = read(FDPFF[0], buffer, sizeof(buffer));
               	 	if(readPipe == -1){
                        	printf("[ERROR] reading pipe\n");
                        	return 0;
                	} else{
				pthread_mutex_lock(t->lock);
            			count++;
             	 		pthread_mutex_unlock(t->lock);
			}
			close(FDPFF[0]);
			wait(&status);
		}
	}
}

int main(int argc, char **argv){

	struct tdata tdados[3];

	pthread_mutex_t mutex;

	strcpy(tdados[0].nome, "veloc");
	tdados[0].lock = &mutex;
	tdados[0].flag = 0;
	strcpy(tdados[0].arg, "VEL ");
	strcat(tdados[0].arg, argv[1]);
	strcpy(tdados[1].nome, "combust");
        tdados[1].lock = &mutex;
	tdados[1].flag = 0;
	strcpy(tdados[1].arg, "GAS");
	strcat(tdados[1].arg, argv[2]);
	strcpy(tdados[2].nome, "temper");
        tdados[2].lock = &mutex;
	tdados[2].flag = 0;
	strcpy(tdados[2].arg, "TEMP");
	strcat(tdados[2].arg, argv[3]);

	pthread_t threads[3];
	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < 3; i++){
		pthread_create(&threads[i], NULL, &routine, &tdados[i]);
	}

	char comando[10];
	while(strcmp(comando, "fim") != 0){
		scanf("%s", comando);

		if(strcmp(comando, "mostra") == 0){
			pthread_mutex_lock(&mutex);
			printf("Informações recolhidas: %d", count);
			pthread_mutex_unlock(&mutex);
		}
	}

	union sigval val;
	val.sival_int = 0;

	for(int i = 0; i < 3; i++){
		tdados[i].flag = 1;
                pthread_join(threads[i], NULL);
		sigqueue(tdados[i].pid, SIGUSR1, val);
        }

	pthread_mutex_destroy(&mutex);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define NPCONTR "npcontr%d"
#define NPC2TORRE "npc2torre"
#define NPAVIAO "npa%d"

struct aviao{
	char nome[15];
	int pid;
};

struct controlador{
	char nome[15];
	int nAvioesAtivos;
};

struct tdados{
	struct controlador *arrayControladores;
	int nControladores;
	int flag;
};

pthread_mutex_t mutex;

void *routineAvioes(void *arg){
	struct tdados *tdata = (struct tdados*) arg;
	struct controlador *controladores = tdata->arrayControladores;
	char fifo_name[10];
	strcpy(fifo_name, getenv("NPA2TORRE"));
	char fifo_name_controlador[10], fifo_aviao_name[10];
	char buffer[20];

	struct aviao airplane;
	int fd_fifo_torre, fd_fifo_aviao, fd_fifo_controlador;
	int nControladores = 0;

	fd_fifo_torre = open(fifo_name, O_RDONLY | O_NONBLOCK);
	if(fd_fifo_torre == -1){
		printf("[ERROR] opening fifo %s\n", fifo_name);
	}

	while(!tdata->nControladores > 0){
		int flagAviao = 0;

		int readFifo = read(fd_fifo_torre, &airplane, sizeof(airplane));
		if(readFifo == -1){
			printf("[ERROR] reading fifo %s\n", fifo_name);
			close(fd_fifo_torre);
			unlink(fifo_name);
			exit(1);
		} else if(readFifo > 0){
			sprintf(fifo_aviao_name, NPAVIAO, airplane.pid);
			fd_fifo_aviao = open(fifo_aviao_name, O_WRONLY | O_NONBLOCK);
			if(fd_fifo_aviao == -1){
				printf("[ERROR] opening fifo %s\n", fifo_aviao_name);
				close(fd_fifo_torre);
                        	unlink(fifo_name);
				exit(1);
			}

			int writeFifo = write(fd_fifo_aviao, &buffer, sizeof(buffer));
			if(writeFifo == -1){
				printf("[ERROR] writing fifo %s\n", fifo_aviao_name);
				close(fd_fifo_torre);
                        	close(fd_fifo_aviao);
				unlink(fifo_name);
				exit(1);
			}

			pthread_mutex_lock(&mutex);
			for(int i = 0; i < tdata->nControladores; i++){
				if(controladores[i].nAvioesAtivos < 5){
					controladores[i].nAvioesAtivos++;
					flagAviao = 1;
					break;
				}
			}
			pthread_mutex_unlock(&mutex);

			char bufferD[50];

			if(flagAviao == 1){
				strcpy(bufferD, "Continuar a viagem\n");
			} else if(flagAviao == 0){
				strcpy(bufferD, "Regressar ao ponto de origem\n");
			}

			fd_fifo_controlador = open(NPC2TORRE, O_WRONLY | O_NONBLOCK);
			if(fd_fifo_controlador == -1){
				printf("[ERROR] writing fifo %s\n", NPC2TORRE);
                                close(fd_fifo_torre);
                                close(fd_fifo_aviao);
                                unlink(fifo_name);
                                exit(1);
			}

			int writeFifoC = write(fd_fifo_controlador, &bufferD, sizeof(bufferD));
			if(writeFifoC == -1){
                                printf("[ERROR] writing fifo %s\n", NPC2TORRE);
                                close(fd_fifo_torre);
                                close(fd_fifo_aviao);
				close(fd_fifo_controlador);
                                unlink(fifo_name);
                                exit(1);
                        }

		}
	}
}

void *routineControladores(void *arg){
	struct tdados *tdata = (struct tdados*) arg;
	struct controlador *array = tdata->arrayControladores;
	struct controlador control;
	int fd_fifo;
	char buffer[20];

	while(!tdata->nControladores > 0){
		fd_fifo = open(NPC2TORRE, O_RDONLY | O_NONBLOCK);
		if(fd_fifo == -1){
			printf("[ERROR] opening fifo %s\n", NPC2TORRE);
			exit(1);
		}

		int readFifo = read(fd_fifo, &control, sizeof(control));
		if(fd_fifo == -1){
                        printf("[ERROR] opening fifo %s\n", NPC2TORRE);
			close(fd_fifo);
                        exit(1);
                }

		pthread_mutex_lock(&mutex);
		for(int i = 0; i < tdata->nControladores; i++){
			if(strcmp(control.nome, array[i].nome) == 0){
				array[i].nAvioesAtivos--;
				break;
			}
		}
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char **argv){

	if(getenv("NPA2TORRE") == NULL){
		return 0;
	}

	char fifo_name[10];
	strcpy(fifo_name, getenv("NPA2TORRE"));

	int fd_fifo_torre;
	int nControladores = atoi(argv[1]);

	struct tdados tdata;
	tdata.nControladores = nControladores;

	pthread_t threads[2];

	fd_fifo_torre = open(fifo_name, O_RDONLY | O_NONBLOCK);
	if(fd_fifo_torre == -1){
		printf("[ERROR] opening fifo %s\n", fifo_name);
		return 0;
	}

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&threads[0], NULL, &routineAvioes, &tdata);
	pthread_create(&threads[1], NULL, &routineControladores, &tdata);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}

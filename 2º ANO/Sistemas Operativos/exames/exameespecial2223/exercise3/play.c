#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int count = 0;

struct tdados{
	char appInstrumentoNome[10];
	int pidInstrumento;
	pthread_mutex_t *lock;
	char *musica;
};

void handler_signal(int sig){
	if(sig == SIGINT){
		printf("Aplication over!\n");
		exit(0);
	} else if(sig == SIGALRM){
		printf("Time over!\n");
		exit(0);
	}

}

void *routine(void *arg){
	struct tdados *tdata = (struct tdados *) arg;
	char *buffer;

	int FDPF[2];
	pipe(FDPF);

	while(1){
		pid_t id = fork();

		if(id == -1){
			printf("[ERROR]\n");
			exit(1);
		} else if(id == 0){
			close(1);
			close(FDPF[0]);
			dup(FDPF[1]);
			close(FDPF[1]);
			execlp(tdata->appInstrumentoNome, tdata->appInstrumentoNome, NULL);
		} else{
			close(FDPF[1]);
			while(1){
				int readF = read(FDPF[0], &buffer, sizeof(buffer));
				if(readF == -1){
					printf("[ERROR] reading\n");
					exit(1);
				}

				pthread_mutex_lock(tdata->lock);
				if(strcmp(tdata->appInstrumentoNome, "guitarra") == 0){
					strcat(tdata->musica, "g");
				} else if(strcmp(tdata->appInstrumentoNome, "piano") == 0){
                                        strcat(tdata->musica, "p");
                                } else if(strcmp(tdata->appInstrumentoNome, "bateria") == 0){
                                        strcat(tdata->musica, "b");
                                }

				strcat(tdata->musica, buffer);
				strcat(tdata->musica, " ");
				pthread_mutex_unlock(tdata->lock);

				count++;
			}
		}
	}
}

int main(int argc, char **argv){

	int time;
	char *musica = "";

	if(getenv("TEMPO") == NULL){
		return 0;
	} else{
		time = atoi(getenv("TEMPO"));
	}

	struct sigaction sa;
	sa.sa_handler = handler_signal;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGALRM, &sa, NULL);

    	alarm(time);

	struct tdados tdata[3];
	pthread_t threads[3];
	pthread_mutex_t mutex;

	strcpy(tdata[0].appInstrumentoNome, "piano");
	strcpy(tdata[1].appInstrumentoNome, "guitarra");
	strcpy(tdata[2].appInstrumentoNome, "bateria");

	tdata[0].lock = &mutex;
	tdata[1].lock = &mutex;
	tdata[2].lock = &mutex;

	tdata[0].musica = musica;
        tdata[1].musica = musica;
        tdata[2].musica = musica;

	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < 3; i++){
		pthread_create(&threads[i], NULL, &routine, &tdata[i]);
	}

	for(int i = 0; i < 3; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);

	printf("%s\n", musica);
	printf("%d notas/acordes\n", count);

	return 0;
}

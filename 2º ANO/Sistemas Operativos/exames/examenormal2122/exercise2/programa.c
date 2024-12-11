#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int countLines = 0;

struct tdata{
	char nameFile[10];
	int flag;
	pthread_mutex_t *lock;
};

int leProximaLinha(char ficheiro[]) {
	// EXEMPLO.
	return 1;
}

void *routine(void *arg){
	struct tdata *tdatat = (struct tdata*) arg;

	while(!tdatat->flag){
		while(leProximaLinha(tdatat->nameFile) == 1){
			pthread_mutex_lock(tdatat->lock);
			countLines++;
			pthread_mutex_unlock(tdatat->lock);
		}

		if(leProximaLinha(tdatat->nameFile) == 0){
			printf("End of file\n");
		} else if(leProximaLinha(tdatat->nameFile) == -1){
			pthread_exit(NULL);
		}
	}
}

int main(int argc, char **argv){

	int countFiles = argc - 1;
	pthread_t threads[countFiles];
	pthread_mutex_t mutex;

	struct tdata tdatas[countFiles];

	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < argc; i++){
		tdatas[i].lock = &mutex;
		tdatas[i].flag = 0;
		strcpy(tdatas[i].nameFile, argv[i + 1]);
		int createThreads = pthread_create(&threads[i], NULL, &routine, &tdatas[i]);
		if(createThreads == -1){
			printf("[ERROR] creating thread %d\n", i);
		}
	}

	for(int i = 0; i < argc; i++){
		tdatas[i].flag = 1;
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	
	printf("Count Lines: %d\n", countLines);

	return 0;
}

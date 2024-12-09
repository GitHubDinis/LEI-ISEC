#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NPALAVRAS 3

struct tdados{
	char palavra[10];
	pthread_mutex_t *lock;
};

int contadorGeral = 0;
char palavras[NPALAVRAS][10] = {"Lisboa", "Porto", "Coimbra"};

int pesquisa(char *nomeFicheiro, char *palavra){return 0;}

void *routine(void *arg){
	struct tdados *t = (struct tdados *) arg;

	pthread_mutex_lock(t->lock);
	contadorGeral += pesquisa(getenv("FICHEIRO"), t->palavra);
	pthread_mutex_unlock(t->lock);

	pthread_exit(NULL);
}

int main(int argc, char **argv){

	if(getenv("FICHEIRO") == NULL){
		return 0;
	}

	struct tdados tdata[NPALAVRAS];

	pthread_mutex_t mutex;
	pthread_t threads[NPALAVRAS];

	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < NPALAVRAS; i++){
		strcpy(tdata[i].palavra, palavras[i]);
		tdata[i].lock = &mutex;
		pthread_create(&threads[i], NULL, &routine, &tdata[i]);
	}

	for(int i = 0; i < NPALAVRAS; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);

	printf("Valor do contador geral: %d", contadorGeral);

	return 0;
}

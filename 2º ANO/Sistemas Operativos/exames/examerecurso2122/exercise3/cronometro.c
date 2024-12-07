#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int getSegundos(){
	return 10; // EXEMPLO
}

int main(int argc, char **argv){
	int tempo_inicial, tempo_final, tempo_max;
	int status, nComandos;

	if(argc < 11){
		nComandos = argc - 1;
	} else {
		return 0;
	}

	if(getenv("TEMPMAX") != NULL){
		tempo_max = atoi(getenv("TEMPMAX"));
	} else{
		return 0;
	}

	int FDPF[nComandos - 1][2];
	for(int i = 0; i < nComandos - 1; i++){
		pipe(FDPF[i]);
	}

	tempo_inicial = getSegundos();

	for (int i = 0; i < nComandos - 1; i++) {
        	pid_t pid = fork();
		if(pid == 0){
			close(STDIN_FILENO);
			dup(FDPF[i][0]);
			close(STDOUT_FILENO);
			dup(FDPF[i][1]);

			for(int j = 0; j < nComandos - 1; j++){
				close(FDPF[j][0]);
				close(FDPF[j][1]);
			}

			execlp(argv[i + 1], argv[i + 1], NULL);
		} else if(pid == -1){
			printf("[ERROR]\n");
			return 0;
		}
	}

	for(int i = 0; i < nComandos - 1; i++){
                close(FDPF[i][0]);
                close(FDPF[i][1]);
	}

	for(int i = 0; i < nComandos - 1; i++){
		wait(&status);
	}

	tempo_final = getSegundos();
	printf("Cronómetro: %d", tempo_final - tempo_inicial);
}

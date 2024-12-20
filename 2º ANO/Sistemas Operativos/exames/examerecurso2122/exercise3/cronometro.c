#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int getSegundos(){
    return (int)time(NULL);
}

int main(int argc, char **argv){
    int tempo_inicial, tempo_final, tempo_max;
    int status, nComandos;

    if(argc < 2){ 
        printf("Número insuficiente de argumentos.\n");
        return 1;
    }

    nComandos = argc - 1; 
	
    if(getenv("TEMPMAX") != NULL){
        tempo_max = atoi(getenv("TEMPMAX"));
    } else {
        tempo_max = 0; 
    }

    int FDPF[nComandos - 1][2];
    for(int i = 0; i < nComandos - 1; i++){
        if(pipe(FDPF[i]) == -1){
            perror("[ERROR] Pipe creation failed");
            return 1;
        }
    }

    tempo_inicial = getSegundos();

    for (int i = 0; i < nComandos; i++) {
        pid_t pid = fork();

        if(pid == 0){ 
            if(i > 0) {
                close(STDIN_FILENO);
                dup(FDPF[i - 1][0]);
            }

            if(i < nComandos - 1) { 
                close(STDOUT_FILENO);
                dup(FDPF[i][1]);
            }

            for(int j = 0; j < nComandos - 1; j++){
                close(FDPF[j][0]);
                close(FDPF[j][1]);
            }

            execlp(argv[i + 1], argv[i + 1], NULL);
        } else if(pid == -1){
            return 1;
        }
    }

    for(int i = 0; i < nComandos - 1; i++){
        close(FDPF[i][0]);
        close(FDPF[i][1]);
    }

    for(int i = 0; i < nComandos; i++){
        wait(&status);
    }

    tempo_final = getSegundos();
    printf("Cronómetro: %d segundos\n", tempo_final - tempo_inicial);

    if(tempo_max > 0 && (tempo_final - tempo_inicial) > tempo_max) {
        printf("Tempo máximo excedido!\n");
    }

    return 0;
}

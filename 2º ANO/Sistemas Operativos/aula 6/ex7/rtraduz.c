#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char letra, palavra[15];
	int id;

	int FDPF[2];
	int erro = pipe(FDPF);

	setbuf(stdout, NULL);

	printf("Letra (x, i, f):");
	scanf("%c", &letra);

	if(letra == 'i' || letra == 'f'){
		fflush(stdout);

		printf("Palavra a traduzir:");
		fgets(palavra, sizeof(palavra), stdin);
		fgets(palavra, sizeof(palavra), stdin);
		//palavra[strlen(palavra) - 1] = '\0';

		pid_t  p = fork();

		if(p == 0){
			if(letra == 'i'){
				palavra[strlen(palavra) - 1] = '\0';
				execl("rding", "rding", palavra, NULL);
				return -1;
			}else if(letra == 'f'){
				close(0);
				dup(FDPF[0]);
				close(FDPF[0]);
				close(FDPF[1]);
				execl("rdfran", "rdfran", NULL);
				printf("Erro no execl");
				return -1;
			}
		} else if(p > 0){
			if(letra == 'f'){
				close(FDPF[0]);
				int size = write(FDPF[1], palavra, strlen(palavra) + 1);
			}
		} else if(p < 0){
			printf("Erro!\n");
		}

		wait(&p);

	}else if(letra == 'x'){
		printf("Termina!\n");
		return 0;
	}

	return 0;
}

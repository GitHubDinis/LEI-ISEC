#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
	char letra, palavra[10];
	int status, id;

	int FDPF[2];
	int erro = pipe(FDPF);

	setbuf(stdout, NULL);

	printf("Char (x, i, f): ");
	scanf(" %c", &letra);
	getchar();

	if(letra == 'i' || letra == 'f'){
		printf("Palavra: ");
		fflush(stdout);
               	scanf(" %s", palavra);

		pid_t p = fork();

		if(p == 0){
			if(letra == 'i'){
				execl("rding", "rding", palavra, NULL);
				return -1;
			} else if(letra == 'f'){
				close(0);
				dup(FDPF[0]);
				close(FDPF[0]);
				close(FDPF[1]);
				execl("rdfran", "rdfran", NULL);
				return -1;
			}
		}else if(p < 0){
			printf("Error!\n");
		} else if(p > 0){
			if(letra == 'f'){
				close(FDPF[0]);
				write(FDPF[1], palavra, strlen(palavra) + 1);
				close(FDPF[1]);
			}
		}

		wait(&p);

	}else if(letra == 'x'){
		return 0;
	}

	return 0;
}

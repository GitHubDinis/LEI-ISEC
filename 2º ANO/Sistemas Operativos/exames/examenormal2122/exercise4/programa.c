#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv){

	int FDPF[2], status;
	pid_t id;
	char operacao[5], buffer[20];
	char operando2[7], operando1[7];

	if(pipe(FDPF) == -1){
		printf("[ERROR] creating pipe\n");
		return 0;
	}

	do{
		printf("[num1] [op] [num2]: ");
		scanf(" %s %s %S", operando1, operacao, operando2);

		if(strcmp(operando1, "fim") == 0){
			return 0;
		}

		id = fork();

		if(id == 0){
			close(STDOUT_FILENO);
			close(FDPF[0]);
			dup(FDPF[1]);
			close(FDPF[1]);
			execlp("scicalc", "scicalc", operando1, operacao, operando2, NULL);
		} else if(id < 0){
			printf("Enganou-se em qualquer coisa!\n");
		} else if(id > 0){
			close(FDPF[1]);
			int readPipe = read(FDPF[0], buffer, sizeof(buffer));
			if(readPipe == -1){
				printf("[ERROR] reading pipe\n");
				return 0;
			}

			printf("o resultado foi: %s\n", buffer);
			wait(&status);
		}
	} while(strcmp(operando1, "fim") != 0);

	close(FDPF[0]);

	return 0;
}

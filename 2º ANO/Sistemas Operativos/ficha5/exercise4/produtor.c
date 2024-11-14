#include "dict.h"

#define PIPE_A "pipe_a"
#define PIPE_B "pipe_b"

int main(){
	char str[256];
	int fd, n;

	char nome[10];

	do{
		printf("Qual PIPE (pipe_a or pipe_b): ");
		scanf(" %s", nome);

		if(strcmp(nome, "pipe_a") == 0){
			fd = open(PIPE_A, O_WRONLY);
		} else if(strcmp(nome, "pipe_b") == 0){
			fd = open(PIPE_B, O_WRONLY);
		}

		if(fd == -1){
			printf("[ERROR] opening FIFO!\n");
			exit(0);
		}

		printf("String: ");
		scanf(" %s", str);

		n = write(fd, str, strlen(str) + 1);

		close(fd);
	}while(strcmp(nome, "sair"));

	return 0;
}

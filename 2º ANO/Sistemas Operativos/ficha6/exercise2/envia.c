#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv){
	char nome[10];
	int fd_pipe, numero;

	fd_pipe = open(argv[1], O_WRONLY);
	if(fd_pipe == -1){
		printf("[ERROR] opening <%s>\n", argv[1]);
		return 0;
	}

	printf("Nome: ");
	scanf(" %s", nome);

	char buffer[20];

	while(1){
		printf("Número: ");
		scanf(" %d", &numero);

		sprintf(buffer, "%s | %d", nome, numero);
		printf("[BUFFER] <%s>\n", buffer);
		int n = write(fd_pipe, buffer, strlen(buffer) + 1);
		if(n == -1){
			printf("[ERROR] writing in %s\n", pipe);
			return 0;
		}
	}

	return 0;
}

#include "dict.h"
#include <signal.h>

int server_fifo_fd, client_fifo_fd; // descritores de ficheiros

void handler_signal(){
	printf("\nServer going off!\n");

	close(server_fifo_fd);
	unlink(SERVER_FIFO);
	exit(0);
}

int main(int argc, char **argv){
	pergunta perg;
	resposta resp;

	int i, res;
	char client_fifo_name[50];
	char *aux;

	struct sigaction sa;
	sa.sa_sigaction = handler_signal;
	sigaction(SIGINT, &sa, NULL);

	res = mkfifo(SERVER_FIFO, 0777);
	if(res == -1){
		printf("\nError creating server FIFO!\n");
		exit(0);
	}

	server_fifo_fd = open(SERVER_FIFO, O_RDWR);
	if(server_fifo_fd == -1){
		printf("\nError opening server FIFO!\n");
		exit(0);
	}

	while(1){
		res = read(server_fifo_fd, &perg, sizeof(perg));
		if(res < sizeof(perg)){
			printf("\n[ERROR] Bytes lidos: %d\n", res);
			continue;
		}

		if(strcmp(perg.palavra, "sair") == 0){
			close(server_fifo_fd);
			unlink(SERVER_FIFO);
			exit(0);
		}

		strcpy(resp.palavra, perg.palavra);
		printf("\nRESPOSTA: [%s]\n", resp.palavra);

		sprintf(client_fifo_name, CLIENT_FIFO, perg.pid_cliente);

		client_fifo_fd = open(client_fifo_name, O_WRONLY);
		if(client_fifo_fd == -1){
			printf("[ERROR] opening client FIFO!\n");
			exit(0);
		}

		res = write(client_fifo_fd, &resp, sizeof(resp));
		if(res == -1){
			printf("[ERROR] writing in client FIFO!\n");
			exit(0);
		}
	}

	close(client_fifo_fd);
	unlink(SERVER_FIFO);

	return 0;
}

#include "dict.h"

int main(int argc, char **argv){
	int server_fifo_fd, client_fifo_fd;
	pergunta perg;
	resposta resp;
	char client_fifo_name[25];
	int read_res;

	perg.pid_cliente = getpid();
	sprintf(client_fifo_name, CLIENT_FIFO, perg.pid_cliente);
	if(mkfifo(client_fifo_name, 0777) == -1){
		printf("[ERROR] creating client FIFO!\n");
		exit(0);
	}

	server_fifo_fd = open(SERVER_FIFO, O_WRONLY);
	if(server_fifo_fd == -1){
		printf("[ERROR] opening server FIFO!\n");
		unlink(client_fifo_name);
		exit(0);
	}

	client_fifo_fd = open(client_fifo_name, O_RDWR);
	if(client_fifo_fd == -1){
		printf("[ERROR] opening client FIFO!\n");
		close(server_fifo_fd);
		unlink(client_fifo_name);
		exit(0);
	}

	while(1){
		printf("String: ");
		fgets(perg.palavra, sizeof(perg.palavra), stdin);
		perg.palavra[strlen(perg.palavra) - 1] = '\0';

		if(strcmp(perg.palavra, "termina") == 0)
			break;

		if(write(server_fifo_fd, &perg, sizeof(perg)) == -1){
			printf("[ERROR] Server has been terminated!\n");
			break;
		};

		read_res = read(client_fifo_fd, &resp, sizeof(resp));
		if(read_res == sizeof(resp)){
			printf("RESPOSTA: [%s]\n", resp.palavra);
		} else{
			printf("SEM RESPOSTA!\n");
		}
	}

	close(client_fifo_fd);
	close(server_fifo_fd);
	unlink(client_fifo_name);

	return 0;
}

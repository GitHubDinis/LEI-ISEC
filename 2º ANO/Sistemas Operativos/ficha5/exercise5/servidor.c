#include "dict.h"
#include <signal.h>

int server_fifo_fd, client_fifo_fd; // descritores de ficheiros

void handler_signal(){
	printf("\nServer going off!\n");

	close(server_fifo_fd);
	unlink(SERVER_FIFO);
	exit(0);
}

void trata_teclado() {
 	int bytes, num1, num2, result;
	char operation;

	scanf("%d %c %d", &num1, &operation, &num2);

	if(operation == '+'){
                result = num1 + num2;
        } else if(operation == '-'){
                result = num1 - num2;
        } else if(operation == 'x'){
                result = num1 * num2;
        } else if(operation == '/'){
                result = (int) num1 / num2;
        }


	printf("\nRESULTADO: [%d]\n", result);
 	fflush(stdout);

 	if(operation == '.') {
 		unlink(SERVER_FIFO);
 		exit(EXIT_SUCCESS);
 	}
}

void game(int fd){
	pergunta perg;
	resposta resp;

	char client_fifo_name[50];
	int res;

	res = read(fd, &perg, sizeof(perg));
	if(res < sizeof(perg)){
		printf("\n[ERROR] Bytes lidos: %d\n", res);
		close(server_fifo_fd);
		unlink(SERVER_FIFO);
		exit(0);
	}

	if(perg.operation == '.'){
		close(server_fifo_fd);
		unlink(SERVER_FIFO);
		exit(0);
	}

	sprintf(client_fifo_name, CLIENT_FIFO, perg.pid_cliente);

	client_fifo_fd = open(client_fifo_name, O_WRONLY);
	if(client_fifo_fd == -1){
		printf("[ERROR] opening client FIFO!\n");
		exit(0);
	}

	if(perg.operation == '+'){
                resp.result = perg.num1 + perg.num2;
        } else if(perg.operation == '-'){
                resp.result = perg.num1 - perg.num2;
        } else if(perg.operation == 'x'){
                resp.result = perg.num1 * perg.num2;
        } else if(perg.operation == '/'){
                resp.result = (int) perg.num1 / perg.num2;
        }

        res = write(client_fifo_fd, &resp, sizeof(resp));
        if(res == -1){
                printf("[ERROR] writing in client FIFO!\n");
                exit(0);
        }
}

int main(int argc, char **argv){
	int i, res;
	char *aux;

	int nfd;
	fd_set read_fd;
	struct timeval tv;

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
		tv.tv_sec = 10;
		tv.tv_usec = 0;

		FD_ZERO(&read_fd);
		FD_SET(0, &read_fd);
		FD_SET(server_fifo_fd, &read_fd);

		nfd = select(server_fifo_fd + 1, &read_fd, NULL, NULL, &tv);

		if(nfd == 0){
			printf("\n[waiting]\n");
			fflush(stdout);
			continue;
		}

		if(nfd == -1){
			printf("\n[error] in select!\n");
			close(server_fifo_fd);
			unlink(SERVER_FIFO);
		}

		if(FD_ISSET(0, &read_fd)){
			trata_teclado();
		}

		if(FD_ISSET(server_fifo_fd, &read_fd)){
			game(server_fifo_fd);
		}
	}

	close(client_fifo_fd);
	unlink(SERVER_FIFO);

	return 0;
}

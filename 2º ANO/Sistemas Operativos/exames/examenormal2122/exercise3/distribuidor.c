#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define PRIOR_FIFO "prior_fifo"
#define NONPRIOR_FIFO "nonprior_fifo"
#define CAIXA_FIFO "caixa_fifo"

struct cliente{
	char nome[10];
};

int main(int argc, char **argv){

	int fd_pipe_p, fd_pipe_np, fd_pipe_caixa;
	struct cliente clientesP[99];
	struct cliente clientesNP[99];

	int countP = 0, countNP = 0;
	int atualP = 0, atualNP = 0;
	int countCaixas = 0;

	char buffer[20];

	if(getenv("NCAIXAS") == NULL){
		return 0;
	}

	int ncaixas = atoi(getenv("NCAIXAS"));

	if(mkfifo(PRIOR_FIFO, 0777) == -1){
		printf("[ERROR] creating fifo %s\n", PRIOR_FIFO);
		return 0;
	}

	if(mkfifo(NONPRIOR_FIFO, 0777) == -1){
		printf("[ERROR] creating fifo %s\n", NONPRIOR_FIFO);
		unlink(PRIOR_FIFO);
		return 0;
	}

	if(mkfifo(CAIXA_FIFO, 0777) == -1){
                printf("[ERROR] creating fifo %s\n", CAIXA_FIFO);
                unlink(PRIOR_FIFO);
                unlink(NONPRIOR_FIFO);
		return 0;
        }

	fd_pipe_p = open(PRIOR_FIFO, O_RDONLY | O_NONBLOCK);
	if(fd_pipe_p == -1){
		printf("[ERROR] opening fifo %s\n", PRIOR_FIFO);
		unlink(PRIOR_FIFO);
		unlink(NONPRIOR_FIFO);
		unlink(CAIXA_FIFO);
		return 0;
	}

	fd_pipe_np = open(NONPRIOR_FIFO, O_RDONLY | O_NONBLOCK);
        if(fd_pipe_np == -1){
                printf("[ERROR] opening fifo %s\n", NONPRIOR_FIFO);
                close(fd_pipe_p);
		unlink(PRIOR_FIFO);
                unlink(NONPRIOR_FIFO);
		unlink(CAIXA_FIFO);
                return 0;
        }

	fd_pipe_caixa = open(NONPRIOR_FIFO, O_RDONLY | O_NONBLOCK);
        if(fd_pipe_caixa == -1){
                printf("[ERROR] opening fifo %s\n", NONPRIOR_FIFO);
                close(fd_pipe_p);
		close(fd_pipe_np);
                unlink(PRIOR_FIFO);
                unlink(NONPRIOR_FIFO);
                unlink(CAIXA_FIFO);
                return 0;
        }

	while(1){
		struct cliente cliente;

		int readP = read(fd_pipe_p, &cliente, sizeof(cliente));
		if(readP == -1){
			printf("[ERROR] reading pipe %s\n", PRIOR_FIFO);
			close(fd_pipe_np);
			close(fd_pipe_p);
			close(fd_pipe_caixa);
                	unlink(PRIOR_FIFO);
                	unlink(NONPRIOR_FIFO);
			unlink(CAIXA_FIFO);
			return 0;
		} else{
			clientesP[countP++] = cliente;
		}

		int readNP = read(fd_pipe_np, &cliente, sizeof(cliente));
		if(readNP == -1){
                        printf("[ERROR] reading pipe %s\n", NONPRIOR_FIFO);
                	close(fd_pipe_np);
                        close(fd_pipe_p);
			close(fd_pipe_caixa);
                        unlink(PRIOR_FIFO);
                        unlink(NONPRIOR_FIFO);
			unlink(CAIXA_FIFO);
                        return 0;
		} else {
			clientesNP[countNP++] = cliente;
		}

		if(countCaixas < ncaixas){
			struct cliente clienteNext;

			if(atualP < countP){
				clienteNext = clientesP[atualP];
			} else if(atualNP < countNP){
				clienteNext = clientesNP[atualNP];
			} else {
				continue;
			}

			// LANÇAR UMA CAIXA?
			execlp("caixa", "caixa", clienteNext.nome, NULL);
			countCaixas++;

			int readCaixa = read(fd_pipe_caixa, &buffer, sizeof(buffer));
			if(readCaixa == -1){
				printf("[ERROR] reading fifo %s\n", CAIXA_FIFO);
				close(fd_pipe_np);
                	        close(fd_pipe_p);
                        	close(fd_pipe_caixa);
                     	   	unlink(PRIOR_FIFO);
                        	unlink(NONPRIOR_FIFO);
                        	unlink(CAIXA_FIFO);
                        	return 0;
			}
		}
	}

	close(fd_pipe_np);
        close(fd_pipe_p);
        close(fd_pipe_caixa);
        unlink(PRIOR_FIFO);
        unlink(NONPRIOR_FIFO);
        unlink(CAIXA_FIFO);
        return 0;
}

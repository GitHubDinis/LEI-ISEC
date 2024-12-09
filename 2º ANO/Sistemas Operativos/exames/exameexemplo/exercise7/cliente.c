#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SERVER_FIFO "serv_files"
#define CLIENT_FIFO "cli_%d"

struct dadosEnviar{
	int pid;
	char nome_fich[20];
};

struct dadosReceber{
	int numP, tamP;
	char pipe2[10], pipe3[10];
};

int main(int argc, char **argv){

	char fifo_name[10];

	struct dadosEnviar dataE;
	dataE.pid = getpid();
	strcpy(dataE.nome_fich, "Ficheiro-versao.bin");

	struct dadosReceber dataR;

	sprintf(fifo_name, CLIENT_FIFO, dataE.pid);
	mkfifo(fifo_name, 0777);

	int fd_server = open(SERVER_FIFO, O_WRONLY);
	write(fd_server, &dataE, sizeof(dataE));

	int fd_client = open(fifo_name, O_RDONLY);
	read(fd_client, &dataR, sizeof(dataR));

	int fd_pipe2 = open(dataR.pipe2, O_RDONLY);
	int fd_pipe3 = open(dataR.pipe3, O_WRONLY);

	FILE *f = fopen(dataE.nome_fich, "r+b");

	for(int i = 0; i < dataR.numP; i++){
		char buffer [1024];

		int readP = read(fd_pipe2, buffer, dataR.tamP * sizeof(char));
		int writeF = fwrite(buffer, sizeof(char), dataR.tamP * sizeof(char), f);

		if(readP == -1 || writeF == -1){
			write(fd_pipe3, "0", sizeof(char));
		} else{
			write(fd_pipe3, "1", sizeof(char));
		}
	}

	return 0;
}

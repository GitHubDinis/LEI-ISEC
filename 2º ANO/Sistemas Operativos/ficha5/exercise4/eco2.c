#include "dict.h"
#include <signal.h>

#define PIPE_A "pipe_a"
#define PIPE_B "pipe_b"

void handler_signal(int s) {
 	unlink(PIPE_A); 
	unlink(PIPE_B);
 	printf("\n ->CC<- \n\n");
 	exit(1);
}

void trata_teclado() {
 	char buffer[200];
 	int bytes;

	fgets(buffer, sizeof(buffer), stdin);

	if((strlen(buffer) > 0) && (buffer[strlen(buffer) - 1] == '\n'))
 		buffer[strlen(buffer)-1] = '\0';

	printf("\nKBD: [%s]\n", buffer);
 	fflush(stdout);

 	if(strcmp(buffer,"sair") == 0) {
 		unlink(PIPE_A); 
		unlink(PIPE_B);
 		exit(EXIT_SUCCESS);
 	}
}

void leEMostraPipes(char * quem, int fd) {
 	char buffer[200];
 	int bytes;

	bytes = read(fd, buffer, sizeof(buffer));
 	buffer[bytes] = '\0';

	if((bytes > 0) && (buffer[strlen(buffer) - 1] == '\n'))
 		buffer[strlen(buffer)-1] = '\0';

	printf("\n%s: (%d bytes) [%s]\n", quem, bytes, buffer);

	if(strcmp(buffer,"sair") == 0) {
 		unlink(PIPE_A);
		unlink(PIPE_B);
		exit(EXIT_SUCCESS);
	}
}

int max(int a, int b) {
	return (a > b) ? a: b;
}

int main(int argc, char **argv){
	int fd_pipe_a, fd_pipe_b;
	int nfd;
	fd_set read_fds;
	struct timeval tv;

	signal(SIGINT, handler_signal);

	if(mkfifo(PIPE_A, 0777) == -1){
		printf("[ERROR] creating PIPE A!\n");
		exit(1);
	}

	if(mkfifo(PIPE_B, 0777) == -1){
		printf("[ERROR] creating PIPE B!\n");
		exit(1);
	}

	fd_pipe_a = open(PIPE_A, O_RDWR | O_NONBLOCK);
	if(fd_pipe_a == -1){
		printf("[ERROR] opening PIPE A!\n");
		exit(1);
	}

	fd_pipe_b = open(PIPE_B, O_RDWR | O_NONBLOCK);
        if(fd_pipe_b == -1){
                printf("[ERROR] opening PIPE B!\n");
        	exit(1);
	}

	while(1){
		tv.tv_sec = 10;
		tv.tv_usec = 0;

		FD_ZERO(&read_fds);
		FD_SET(0, &read_fds);
		FD_SET(fd_pipe_a, &read_fds);
		FD_SET(fd_pipe_b, &read_fds);

		nfd = select(max(fd_pipe_a, fd_pipe_b) + 1, &read_fds, NULL, NULL, &tv);

		if(nfd == 0){
			printf("\n[WAITING]\n");
			fflush(stdout);
			continue;
		}

		if(nfd == -1){
			printf("[ERROR] select!\n");
			close(fd_pipe_a);
			close(fd_pipe_b);
			unlink(PIPE_A);
			unlink(PIPE_B);
		}

		if(FD_ISSET(0, &read_fds)){
			trata_teclado();
		}

		if(FD_ISSET(fd_pipe_a, &read_fds)){
			leEMostraPipes("A", fd_pipe_a);
		}

		if(FD_ISSET(fd_pipe_b, &read_fds)){
			leEMostraPipes("B", fd_pipe_b);
		}
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define PIPE "pipeSO"

void handler_signal(int signal, siginfo_t *info, void *extra){
	if(signal == SIGINT){
		printf("a sair...\n");
		unlink(PIPE);
		exit(0);
	}
}

int main(){
	setbuf(stdout, NULL);

	char str[256];
	int fd, n;

	struct sigaction sa;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = handler_signal;
	sigaction(SIGINT, &sa, NULL);

	mkfifo(PIPE, 0777);

	do{
		fd = open(PIPE, O_RDONLY);
		n = read(fd, str, sizeof(str) - 1);
		str[n - 1] = '\0';
		printf("[ECO] Lido %i bytes do pipe: %s\n", n, str);
	}while(strcmp(str, "terminar"));

	unlink(PIPE);
	return 0;
}


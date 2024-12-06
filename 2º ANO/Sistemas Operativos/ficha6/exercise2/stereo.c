#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define P_ESQ "p_esq"
#define P_DIR "p_dir"

struct estrutura{
	int fd;
	int threadCancel;
	char nomePipe[10];
};

int fd_esq, fd_dir;
pthread_t threadStereo[2];
struct estrutura stct[2];

void *handler_thread(void *arg){
	struct estrutura *s = (struct estrutura *)arg;
	char buffer[20];

	while(!s->threadCancel){
		int n = read(s->fd, buffer, strlen(buffer));
		if(n == -1){
			printf("[ERROR] reading from fifo\n");
		}
		sleep(1);
		printf("[%s] - %s", s->nomePipe, buffer);
	}
}

void handler_signal(){
	printf("[ADEUS]\n");
	close(fd_esq);
	close(fd_dir);
	unlink(P_ESQ);
	unlink(P_DIR);
	exit(0);
}

int main(int argc, char **argv){
	setbuf(stdout, NULL);

	struct sigaction sa;
	sa.sa_handler = handler_signal;
	sigaction(SIGINT, &sa, NULL);

	if(mkfifo(P_ESQ, 0777) == -1){
		printf("[ERROR] creating fifo\n");
		return 0;
	}

	if(mkfifo(P_DIR, 0777) == -1){
		printf("[ERROR] creating fifo\n");
		return 0;
	}

	fd_esq = open(P_ESQ, O_RDWR);
	if(fd_esq == -1){
		printf("[ERROR] opening fifo\n");
		unlink(P_ESQ);
		unlink(P_DIR);
		return 0;
	}

	fd_dir = open(P_DIR, O_RDWR);
	if(fd_dir == -1){
		printf("[ERROR] opening fifo\n");
		close(fd_esq);
		unlink(P_ESQ);
                unlink(P_DIR);
		return 0;
	}

	stct[0].fd = fd_esq;
	stct[1].fd = fd_dir;

	strcpy(stct[0].nomePipe, P_ESQ);
	strcpy(stct[1].nomePipe, P_DIR);

	stct[0].threadCancel = 0;
	stct[1].threadCancel = 0;

	if(pthread_create(&threadStereo[0], NULL, handler_thread, &stct[0]) == -1){
		printf("[ERROR] creating thread\n");
		return 0;
	}

	if(pthread_create(&threadStereo[1], NULL, handler_thread, &stct[1]) == -1){
		printf("[ERROR] creating thread\n");
		return 0;
	}

	while(1){

	}

	stct[0].threadCancel = 1;
	pthread_join(threadStereo[0], NULL);

	stct[1].threadCancel = 1;
        pthread_join(threadStereo[1], NULL);

	unlink(P_ESQ);
	unlink(P_DIR);

	return 0;
}

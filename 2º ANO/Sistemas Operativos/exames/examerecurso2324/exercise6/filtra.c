#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>

int bytesTotal = 0;
int id1, id2;

void handler_signal(int sig){
	union sigval val;
	val.sival_int = 1;
	sigqueue(id1, SIGUSR2, val);
	sigqueue(id2, SIGUSR2, val);
	printf("\nTempo limite atingido. Bytes totais transferidos: %d\n", bytesTotal);
}

int main(int argc, char **argv){

	int status;
	int FDPF[2], FDPFF[2];
	pipe(FDPF); pipe(FDPFF);

	char buffer[50];
	int duracao;

	if(argc == 4){
		duracao = atoi(argv[3]);

		signal(SIGALRM, handler_signal);
        	alarm(duracao);
	}

	pid_t id = fork();
	id1 = id;

	if(id == 0){
		close(STDOUT_FILENO);
		dup(FDPF[1]);
		close(FDPF[1]);
		close(FDPF[0]);
		execlp(argv[1], argv[1], NULL);
	} if(id < 0){
		printf("[error]\n");
		return 0;
	} else if(id > 0){

		close(FDPF[1]);
                bytesTotal += read(FDPF[0], buffer, sizeof(buffer));
                close(FDPF[0]);

                for (int i = 0; i < strlen(buffer); i++) {
                        buffer[i] = toupper(buffer[i]);
                }

		int statuss;
		pid_t idd = fork();
		id2 = idd;

		if(idd == 0){
			close(STDIN_FILENO);
                	dup(FDPFF[0]);
                	close(FDPFF[0]);
        	        close(FDPFF[1]);
	                execlp(argv[2], argv[2], NULL);
		} else if(idd < 0){
			printf("[error]\n");
                	return 0;
		} else if(idd > 0){
			close(FDPFF[0]);
                	bytesTotal += write(FDPFF[1], buffer, sizeof(buffer));
                	close(FDPFF[1]);

			wait(&statuss);
		}

		wait(&status);
	}

	printf("\nExecução concluída. Bytes totais transferidos: %d\n", bytesTotal);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void receiveSignal(int s, siginfo_t *i, void *v){
	int numRec = i->si_value.sival_int;

	if(numRec == 1){
		printf("\nDemasiado Grande!");
	}else if(numRec == -1){
		printf("\nDemasiado Pequeno!");
	}else if(numRec == 0){
		printf("\nAcertou!\n");
	}
}

int main(int argc, char **argv){
	printf("PID: [%d]", getpid());
	int pid = atoi(argv[1]);

	union sigval val;

	do{
		printf("Number: ");
		scanf("%d", &val.sival_int);
		sigqueue(pid, SIGUSR1, val);

		struct sigaction sa;
		sa.sa_sigaction = receiveSignal;
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
		sigaction(SIGUSR2, &sa, NULL);
	}while(1);

	return 0;
}

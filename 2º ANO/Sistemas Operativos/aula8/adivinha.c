#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void recebeSinal(int s, siginfo_t *i, void *v){
	int n = i->si_value.sival_int;

	if(n == 1){
		printf("\nDemasiado Grande!");
	}else if(n == -1){
		printf("\nDemasiado Pequeno!");
	}else if(n == 0){
		printf("\nAcertou!\n");
	}
}

int main(int argc, char *argv[]){
	int pid;

	printf("\nPID do programa: [%d]", getpid());

	printf("\nPID do sorteia: ");
	scanf("%d", &pid);

	union sigval val;

	do{
		printf("\nNumero: ");
		scanf("%d", &val.sival_int);
		sigqueue(pid, SIGUSR1, val);

		struct sigaction sa;
		sa.sa_sigaction = recebeSinal;
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
		sigaction(SIGUSR2, &sa, NULL);
	} while(1);

	int numero;

	return 0;
}

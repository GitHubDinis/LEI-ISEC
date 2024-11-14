#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int pid = 0;
union sigval val;

void recebeSinal(int s, siginfo_t *i, void *v){
	int n = i->si_value.sival_int;

	if(n == 1){
		printf("Demasiado Grande!\n");
	} else if(n == -1){
		printf("Demasiado Pequeno!\n");
	} else if(n == 0){
		printf("\nAcertou!\n");
	} else if(n == 2){
		printf("\nOutro Jogador Acertou! Recomeça!\n");
	}
}

void sair(int s){
	val.sival_int = 0;
        sigqueue(pid, SIGUSR1, val);
	printf("\nSinal com Valor [%d] enviado! Adeus!\n", val.sival_int);
	exit(1);
}

int main(int argc, char *argv[]){
	printf("\nPID do programa: [%d]", getpid());

	printf("\nPID do sorteia: ");
	scanf("%d", &pid);

	do{
		struct sigaction sa;
                sa.sa_sigaction = recebeSinal;
                sa.sa_flags = SA_RESTART | SA_SIGINFO;

		printf("\nNumero: ");
		scanf("%d", &val.sival_int);
		sigqueue(pid, SIGUSR1, val);

		sigaction(SIGUSR2, &sa, NULL);

		struct sigaction sac;
	        sac.sa_handler = sair;
        	sigaction(SIGINT, &sac, NULL);
	} while(1);

	return 0;
}

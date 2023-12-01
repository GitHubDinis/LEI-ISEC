#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
int num1;
int numAdivinha = 0;
void sair(int s)
{
	printf("\nAdeus - Pontos [%d]\n", numAdivinha);
	exit(1);
}
void sorteia()
{
	srand(time(NULL));
	num1 = rand() % 100;
	// printf("Numero [%d]\n",num1);
}

void jogo(int s, siginfo_t *i, void *v)
{
	int n = i->si_value.sival_int;
	union sigval val;

	if (n > num1){
		printf("Resposta de [%d] - Demasiado Grande\n", i->si_pid);
		val.sival_int = 1;
		sigqueue(i->si_pid, SIGUSR2, val);
	}else if (n < num1){
		printf("Resposta de [%d] -Demasiado Pequeno\n", i->si_pid);
		val.sival_int = -1;
		sigqueue(i->si_pid, SIGUSR2, val);
	}else if (n == num1){
		numAdivinha++;
		printf("Resposta de [%d] -Acertou\n", i->si_pid);
		val.sival_int = 0;
		sigqueue(i->si_pid, SIGUSR2, val);
		sorteia();
	}
}
int main()
{
	setbuf(stdout, NULL);
	struct sigaction sa;
	sa.sa_sigaction = jogo;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	struct sigaction sac;
	sa.sa_handler = sair;
	sigaction(SIGINT, &sac, NULL);
	printf("O meu PID - [%d]", getpid());
	sorteia();
	do
	{ 	} while (1);
}

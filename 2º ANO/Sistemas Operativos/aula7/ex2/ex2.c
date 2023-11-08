#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int n = 20;
int pontuacao = 0;
int perdeu = 0;

void jogo(){
	srand(time(NULL));
	int num1 = rand() % 100;
	int num2 = rand() % 100;
	int soma = num1 + num2, somaUser;
	n--;

	printf("\nResultado [%d] + [%d]:\n", num1, num2);
	if(scanf("%d", &somaUser) != 1){
		perror("\nNada - Perdeu!\n");
	}
	if(soma == somaUser){
		pontuacao++;
		printf("\nAcertou e tem [%d] pontos\n", pontuacao);
	} else{
		printf("\nPerdeu!\n");
		if(++perdeu == 2)
			exit(1);
		else
			printf("\nTem mais uma tentativa!\n");
	}
}

void handler_funcSinal(int signum, siginfo_t *info, void *secret){
	printf("\nAcabou o tempo!\n");
	exit(1);
}

int main(){
	int i = 0;
	struct sigaction sa;
	sa.sa_sigaction = handler_funcSinal;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;

	while(1){
		if(i == 5){
			exit(1);
		} else{
			alarm(n);
			jogo();
		}
		i++;
	}
	return 0;
}

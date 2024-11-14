#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

void handler_signal(){
	printf("ai\n");
	++count;
	if(count == 5){
		printf("ok, pronto!\n");
		exit(1);
	}
}

int main(){
	char nome[10];
	struct sigaction sa;
	sa.sa_sigaction = handler_signal;
	sigaction(SIGINT, &sa, NULL);

	printf("PID: %d", getpid());

	while(1){
		printf("Nome: ");
		fgets(nome, sizeof(nome), stdin);

		if(strcmp(nome, "sair") == 0){
			return 1;
		} else{
			printf("Olá %s!\n", nome);
		}
	}

	return 0;
}

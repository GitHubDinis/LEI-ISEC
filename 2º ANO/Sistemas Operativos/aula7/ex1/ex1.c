#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int contador = 0;

void handler_funcSinal(int signum, siginfo_t *info, void *secret){
	printf("\nai\n");
	++contador;
	if(contador == 5){
		printf("\nok, pronto!\n");
		exit(1);
	}
}

int main(){
	char nome[100];
	struct sigaction sa;
	sa.sa_sigaction = handler_funcSinal;
	// sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);

	while(1){
		printf("Pede nome de utilizador:");
		fgets(nome, sizeof(nome), stdin);
        	nome[strlen(nome) - 1] = '\0';

		if(strcmp(nome, "sair") == 0){
			return 1;
		} else{
			printf("Nome: %s\n", nome);
		}
	}
	return -1;
}

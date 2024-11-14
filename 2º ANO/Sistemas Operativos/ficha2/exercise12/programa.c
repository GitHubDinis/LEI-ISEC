#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	char nome[10];
	printf("Environment Variable Name: ");
	scanf("%s", nome);

	char valor[10];
	printf("Environment Variable Value: ");
	scanf("%s", valor);

	setenv(nome, valor, 1);

	const char *ambiente = getenv(nome);

	if(ambiente != NULL){
		printf("Name: %s | Valor: %s\n", nome, valor);
	} else {
		printf("Not found!\n");
	}
}

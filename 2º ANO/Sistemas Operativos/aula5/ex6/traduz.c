#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	char letra;
	char palavra[10];
	int id;
	int status;

	setbuf(stdout, NULL);

	do{
		printf("Letra (x, i, f):");
		scanf("%c", &letra);

		if(letra == 'i' || letra == 'f'){
			printf("Palavra a traduzir: ");
			fflush(stdout);
			scanf(" %s", palavra);

			id = fork();

			if(id == 0){
				if(letra == 'i'){
					execl("ding", "ding", palavra, NULL);
				}else if(letra == 'f'){
					execl("dfran", "dfran", palavra, NULL);
				}
			}else if(id < 0){
				printf("Erro!\n");
			}else if(id > 0){
				wait(&status);
			}
		}
	}while(letra != 'x');

	return 0;
}

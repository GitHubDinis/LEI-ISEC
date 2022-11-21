#include <stdio.h>
#include "users_lib.h"
#include "structs.h"
#include <string.h>
#include <ctype.h>

int comandos();
int loadItensFile(char * pathname);
int isString(char s[]);
int promotor();

int main(){

	int opcao, numberuser;
	int teste, teste1;

	printf("Deseja testar que funcionalidade?\n");
	printf("1 - Comandos\n");
	printf("2 - Execução do promotor\n");
	printf("3 - Utilizadores\n");
	printf("4 - Itens\n");
	scanf("%d", &opcao);
	putchar('\n');

	if(opcao == 1){
		comandos();
	}else if(opcao == 2){
		promotor();
		//execl("./promotor_oficial", "promotor_oficial", NULL);
	}else if(opcao == 3){
		numberuser = loadUsersFile("/home/dinisfalcao/trabalho/users.txt");
		printf("%d lidos!\n", numberuser);
		teste = getUserBalance("dinis");
		if(teste == -1){
			printf("Erro!\n");
		}else{
			printf("Saldo do user: %d\n", teste);
		}
		updateUserBalance("dinis", teste - 1);
		teste1 = saveUsersFile("/home/dinisfalcao/trabalho/users.txt");
		if(teste1 == 0){
			printf("Sucesso!\n");
		}else{
			printf("Insucesso!\n");
		}
	}else if(opcao == 4){
		loadItensFile("/home/dinisfalcao/trabalho/itens.txt");
	}
	return 0;
}

int comandos(){
	const char s[1] = " ";
        char cmd[80];
        char *token;
        int count = 0;

	do{

		count = 0;
		printf("\nComando:");
	       	//scanf("%s", &cmd);
		fgets(cmd, 80, stdin);
		//cmd[strlen(cmd) - 1] = '\0';

		/* get the first token */
		token = strtok(cmd, s);

		if (strcmp(token, "users") == 0){
		       	printf("\nComando certo!");
			count++;
			if (count == 1) {
			        printf("\nNumero de argumentos correto!\n");
			}else{
			        printf("\nNumero de argumentos errado!\n");
			}
		}else if (strcmp(token, "list") == 0){
			printf("\nComando certo!");
			count ++;
			if(count == 1){
				printf("\nNumero de argumentos correto!\n");
			}else{
				printf("\nNumero de argumentos errado!\n");
			}
		}else if (strcmp(token, "kick") == 0){
			printf("\nComando Certo!");
			while(token != NULL){
				count ++;
				if(count == 2){
					if(isString(token) == 0){
						printf("\nPosicao %d e string, correto!\n", count);
					}else{
						printf("\nPosicao %d e numero, incorreto!\n", count);
					}
				}
				token = strtok(NULL, s);
			}
			if(count == 2){
				printf("\nNumero de argumentos correto!\n");
			}else{
				printf("\nNumero de argumentos errado!\n");
			}
		}else if(strcmp(token, "prom") == 0){
			printf("\nComando Certo!");
			count ++;
			if(count == 1){
				printf("\nNumero de argumentos correto!\n");
			}else{
				printf("\nNumero de argumentos errado!\n" );
			}
		}else if(strcmp(token, "reprom") == 0){
			printf("\nComando Certo!");
			count ++;
			if(count == 1){
				printf("\nNumero de argumentos correto!\n");
			}else{
				printf("\nNumero de argumentos errado!\n");
			}
		}else if(strcmp(token, "cancel") == 0){
			printf("\nComando Certo!");
			while(token != NULL){
				count ++;
				if(count == 2){
					if(isString(token) == 0){
						printf("\nPosicao %d e string, correto!\n", count);
					}else{
						printf("\nPosicao %d e numero, incorreto!\n", count);
					}
				}
				token = strtok(NULL, s);
			}
			if(count == 2){
				printf("\nNumero de argumentos correto!\n");
			}else{
				printf("\nNumero de argumentos errado!\n");
			}
		}else if(strcmp(token, "close") == 0){
			printf("\nComando Certo!");
			count++;
			if(count == 1){
				printf("\nNumero de argumentos correto!\n");
				return 0;
			}else{
				printf("\nNumero de argumentos errado!\n");
			}
		}

	}while(1);

	return 0;
}

int loadItensFile(char *pathname){

	int count = 0;
	item item1;

	FILE *f;

	f = fopen(pathname, "rt");

	if(f == NULL){
		printf("Erro na abertura do ficheiro!");
		return -1;
	}else{
		while(fscanf(f, "%d %s %s %d %d %d %s %s", &item1.iditem,
		item1.nome, item1.categoria, &item1.valor_atual, &item1.valor_comprar,
		&item1.duracao, item1.userVende, item1.userLicita) != -1){
			count++;
			printf("%d %s %s %d %d %d %s %s\n",item1.iditem,
			item1.nome, item1.categoria, item1.valor_atual,
			item1.valor_comprar, item1.duracao, item1.userVende,
			item1.userLicita);
		}
		//while(!feof(f)){
			//fread(&bufferItem,sizeof(Item),1,f);
			//count++;
		//}
	}

	printf("\n%d itens lidos!\n", count);
	//return count;

	fclose(f);
	return 0;
}

int isString(char s[]){

	for(int i = 0; s[i] != '\0'; i++){
		if(isdigit(s[i]) == 0){
			return 0;
		}
	return 1;
	}
}

int promotor(){

	int fd[2];
	pipe(fd);
	int pid = fork();

	if(pid == 0){ //filho
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execl("./promotor_oficial", "promotor_oficial", NULL);
		//printf("Estou aqui!\n");
	}else if(pid > 0){ //pai
		close(fd[0]);
		write(fd[1], "Promotor: ", 15);
		//printf("Estou aqui\n");
	}
	return 0;
}

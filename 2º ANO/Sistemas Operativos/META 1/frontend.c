#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "users_lib.h"

int comandos();
int isString(char s[]);

int main(int argc, char * argv[]){

	char * username;
	char * password;

	if(argc == 3){
		printf("Number of arguments correct!\n");
		username = argv[1];
		password = argv[2];
		printf("Login do %s com a password %s\n", username, password);
		comandos();
	}else{
		printf("Number of arguments incorrect!\n");
		return 0;
	}

	return 0;
}

int comandos() {

    	const char space[1] = " ";
    	char cmd[80];
    	char *token;
    	int count = 0;

	do{

		count = 0;

		printf("Comando pretendido:\n");
	        fgets(cmd, 80, stdin);
		cmd[strlen(cmd) - 1] = '\0';
		/* get the first token */
	    	token = strtok(cmd, space);

	    	/* get the rest */
	        if (strcmp(token, "sell") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
				if(count == 2 || count == 3){
					if(isString(token) == 0){
						printf("\nPosicao %d e string, correto!", count);
					}else{
						printf("\nPosicao %d e numero, incorreto!\n");
					}
				}else if(count == 4 || count == 5 || count == 6){
					if(isString(token) == 1){
						printf("\nPosicao %d e numero, correto!", count);
					}else{
						printf("Posicao %d e string, incorreto!\n", count);
					}
				}
	                	token = strtok(NULL, space);
	            	}
	            	if (count == 6) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "list") == 0) {
	            	printf("\nComando certo!");
		    	while(token != NULL){
	                	count++;
		    		token = strtok(NULL, space);
		    	}
	            	if (count == 1) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	       	}
	        } else if (strcmp(token, "licat") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
				if(count == 2){
					if(isString(token) == 0){
						printf("\nPosicao %d e string, correto!\n", count);
					}else{
						printf("\nPosicao %d e numero, incorreto!\n", count);
					}
				}
	                	token = strtok(NULL, space);
	            	}
	            	if (count == 2) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	        }
	        } else if (strcmp(token, "lisel") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
				if(count == 2){
					if(isString(token) == 0){
						printf("\nPosicao %d e string, correto!\n", count);
					}else{
						printf("\nPosicao %d e numero, incorreto!\n", count);
					}
				}
	               	 	token = strtok(NULL, space);
	            	}
	            	if (count == 2) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "lival") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
				if(count == 2){
					if(isString(token) == 1){
						printf("\nPosicao %d e numero, correto!\n", count);
					}else{
						printf("\nPosicao %d e string, incorreto!\n", count);
					}
				}
	                	token = strtok(NULL, space);
	            	}
	            	if (count == 2) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	        	}
	        } else if (strcmp(token, "litime") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
				if(count == 2){
					if(isString(token) == 1){
						printf("\nPosicao %d e numero, correto!\n", count);
					}else{
						printf("\nPosicao %d e string, incorreto!\n", count);
					}
				}
	                	token = strtok(NULL, space);
	            	}
	            	if (count == 2) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "time") == 0) {
	            	printf("\nComando certo!");
		        	while(token != NULL){
	                		count++;
					token = strtok(NULL, space);
				}
	            	if (count == 1) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "buy") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
					if(count == 2 || count == 3){
						if(isString(token) == 1){
							printf("\nPosicao %d e numero, correto!\n", count);
						}else{
							printf("\nPosicao %d e string, incorreto!\n", count);
						}
					}
	                	token = strtok(NULL, space);
	            	}
	            	if (count == 3) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "cash") == 0) {
	            	printf("\nComando certo!");
		    	while(token != NULL){
	                	count++;
				token = strtok(NULL, space);
		    	}
	            	if (count == 1) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "add") == 0) {
	            	printf("\nComando certo!");
	            	while (token != NULL) {
	                	count++;
				if(count == 2){
					if(isString(token) == 1){
						printf("\nPosicao %d e numero, correto!\n", count);
					}else{
						printf("\nPosicao %d e string, incorreto!\n", count);
					}
				}
	                	token = strtok(NULL, space);
	            	}
	            	if (count == 2) {
	                	printf("\nNumero de argumentos correto!\n");
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        } else if (strcmp(token, "exit") == 0) {
	            	printf("\nComando certo!");
		    	while(token != NULL){
	                	count++;
				token = strtok(NULL, space);
		    	}
	            	if (count == 1) {
	                	printf("\nNumero de argumentos correto!\n");
				return 0;
	            	}else{
	                	printf("\nNumero de argumentos errado!\n");
	            	}
	        }
	}while(1);

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

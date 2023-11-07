#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	char opc[5];
	setbuf(stdout, NULL);

	printf("Introduz caracteres:");
	scanf("%s", opc);

	if(strcmp(opc, "port") == 0){
		execlp("./port", NULL);
	}else if(strcmp(opc, "ing") == 0){
		execlp("./ing", NULL);
	}

	printf("Missao Cumprida!\n");

	return 0;
}

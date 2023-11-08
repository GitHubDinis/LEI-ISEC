#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	setbuf(stdout, NULL);
	char *fran[] = {"bonjour", "aujourd'hui", "hier", "lundi", "mardi"};
	char *port[] = {"ola", "hoje", "ontem", "segunda", "terca"};

	char palavra[15];

	fgets(palavra, sizeof(palavra), stdin);
	palavra[strlen(palavra) - 1] = '\0';

	for(int i = 0; i < 5; i++){
		if(strcmp(palavra, port[i]) == 0){
			printf("%s\n", fran[i]);
			fflush(stdout);
		}
	}

	return 0;
}

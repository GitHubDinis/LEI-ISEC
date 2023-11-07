#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	setbuf(stdout, NULL);
	char *fran[] = {"bonjour", "aujourd'hui", "hier", "lundi", "mardi"};
	char *port[] = {"ola", "hoje", "ontem", "segunda", "terca"};

	for(int i = 0; i < 5; i++){
		if(strcmp(argv[1], port[i]) == 0){
			printf("%s\n", fran[i]);
			fflush(stdout);
		}
	}

	return 0;
}

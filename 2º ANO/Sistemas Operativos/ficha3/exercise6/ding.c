#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	setbuf(stdout, NULL);
	char *palavra[] = {"Um", "Dois", "Três", "Quatro", "Cinco"};
	char *tradution[] = {"One", "Two", "Three", "Four", "Five"};

	// RESOLVEU A FALTA DE SEGMENTAÇÃO:
	int size = sizeof(palavra) / sizeof(palavra[0]);

	for(int i = 0; i < size; i++){
		if(strcmp(argv[1], palavra[i]) == 0){
			printf("Translator: %s\n", tradution[i]);
			fflush(stdout);
		}
	}

	return 0;
}

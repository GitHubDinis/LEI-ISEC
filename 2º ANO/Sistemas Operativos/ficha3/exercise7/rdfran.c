#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	setbuf(stdout, NULL);
	char *palavra[] = {"Um", "Dois", "Três", "Quatro", "Cinco"};
	char *traducion[] = {"Un", "Deux", "Trois", "Quatre", "Cinq"};

	char word[10];

	// RESOLVEU A FALTA DE SEGMENTAÇÃO:
	int size = sizeof(palavra) / sizeof(palavra[0]);
	fgets(word, sizeof(word), stdin);

	for(int i = 0; i < size; i++){
		if(strcmp(word, palavra[i]) == 0){
			printf("Traduction: %s\n", traducion[i]);
			fflush(stdout);
		}
	}
	

	return 0;
}

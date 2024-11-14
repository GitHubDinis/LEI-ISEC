#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	char characters[10];
	printf("Enter Characters: ");
	scanf("%s", characters);

	if(strcmp(characters, "port") == 0){
		execlp("./port", NULL);
	} else if(strcmp(characters, "ing") == 0){
		execlp("./ing", NULL);
	}

	return 0;
}


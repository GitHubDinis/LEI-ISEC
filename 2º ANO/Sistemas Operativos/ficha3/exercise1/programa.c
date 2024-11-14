#include <stdio.h>

int main(int argc, char **argv){
	char input[100];

	printf("Enter Characters: ");
    	fgets(input, sizeof(input), stdin);

	printf("%s", input);

	return 0;
}

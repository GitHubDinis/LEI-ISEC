#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	if(strcmp(argv[1], "port") == 0){
		execlp("./port", NULL);
	} else if(strcmp(argv[1], "ing") == 0){
		execlp("./ing", NULL);
	}

	return 0;
}

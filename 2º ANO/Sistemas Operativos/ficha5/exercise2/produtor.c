#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define PIPE "pipeSO"

int main(){
	char str[256];
	int fd, n;

	do{
		fd = open(PIPE, O_WRONLY);

		if(fd == -1){
			printf("Error FIFO!\n");
			exit(0);
		}

		printf("String: ");
		scanf(" %s", str);

		n = write(fd, str, strlen(str) + 1);

		close(fd);
	}while(strcmp(str, "terminar"));

	return 0;
}

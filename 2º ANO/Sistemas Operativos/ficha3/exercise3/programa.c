#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	int nStar = atoi(argv[1]);
	int nSec = atoi(argv[2]);

	setbuf(stdout, NULL);

	if(argc == 3){
		for(int i = 0; i < nStar; i++){
			printf("*\n");
			sleep (nSec);
		}
	} else {
		return 0;
	}

	return 0;
}

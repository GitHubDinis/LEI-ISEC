#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	int nstar = atoi(argv[1]);
	int nsec = atoi(argv[2]);

	setbuf(stdout, NULL);

	if(argc == 3){
		for(int i = 0; i < nstar; i++){
			printf("*\n");
			sleep (nsec);
		}
	} else {
		return 0;
	}
	return 0;
}

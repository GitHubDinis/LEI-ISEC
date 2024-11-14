#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

void handler_signal(){
	if(count < 5){
		printf("ai ");
		count++;
	} else{
		exit(1);
	}
}

int main(){
	setbuf(stdout, NULL);
	signal(SIGINT, handler_signal);

	char name[10];

	while(1){
		if(strcmp(name, "sair") == 0){
			return 0;
		} else{
			printf("Name: ");
			scanf(" %s", name);
			printf("Olá %s", name);
		}
	}
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int n = 20;
int points = 0;
int tried = 0;

void game(){
	srand(time(NULL));
	int num;
	int num1 = rand() % 100;
	int num2 = rand() % 100;
	int res = num1 + num2;

	printf("Sum between [%d] and [%d]: ", num1, num2);
	scanf("%d", &num);
	n--;

	if(num == res){
		printf("Correct!\n");
		points++;
		printf("Points: %d\n", points);
	} else{
		printf("Incorrect!\n");
		if(++tried == 2){
			printf("Points: %d\n", points);
			exit(1);
		} else{
			printf("One more try!\n");
		}
	}
}

void handler_signal(int signum, siginfo_t *info, void *secret){
	printf("\nAcabou o tempo!\n");
	exit(1);
}

int main(int argc, char **argv){
	struct sigaction sa;
	sa.sa_sigaction = handler_signal;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;

	while(1){
		alarm(n);
		game();
	}

	return 0;
}

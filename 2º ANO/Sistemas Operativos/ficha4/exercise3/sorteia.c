#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

int numS = 0;
int points = 0;

void exit(int signal){
	printf("\nGoodbye! - Points: [%d]\n", points);
	exit(1);
}

void sort(){
	srand(time(NULL));
	numS = rand() % 100;
}

void game(int s, siginfo_t *i, void *v){
	int numUser = i->si_value.sival_int;
	union sigval val;

	if(numUser > numS){
		printf("\nDemasiado grande! [%d]\n", i->si_pid);
		val.sival_int = 1;
		sigqueue(i->si_pid, SIGUSR2, val);
	} else if(numUser < numS){
		printf("\nDemasiado pequeno! [%d]\n", i->si_pid);
		val.sival_int = -1;
		sigqueue(i->si_pid, SIGUSR2, val);
	} else if(numUser == numS){
		points++;
		printf("\nAcertou! [%d]\n", i->si_pid);
		val.sival_int = 0;
		sigqueue(i->si_pid, SIGUSR2, val);
		sort();
	}
}

int main(int argc, char **argv){
	setbuf(stdout, NULL);

	struct sigaction sa;
	sa.sa_sigaction = game;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);

	struct sigaction sac;
	sac.sa_handler = exit;
	sigaction(SIGINT, &sac, NULL);

	printf("PID: [%d]\n", getpid());

	sort();

	do{

	}while(1);

	return 0;
}

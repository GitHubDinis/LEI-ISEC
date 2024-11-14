#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
	char letra, palavra[10];
	int status, id;

	setbuf(stdout, NULL);

	do{
		printf("Char (x, i, f): ");
		scanf(" %c", &letra);
		getchar();

		if(letra == 'i' || letra == 'f'){
			printf("Palavra: ");
			fflush(stdout);
                	scanf(" %s", palavra);

			id =  fork();

			if(id == 0){
				if(letra == 'i'){
					execl("ding", "ding", palavra, NULL);
				} else if(letra == 'f'){
					execl("dfran", "dfran", palavra, NULL);
				}
			}else if(id < 0){
				printf("Error!\n");
			} else if(id > 0){
				wait(&status);
			}
		}
	}while(letra != 'x');

	return 0;
}

#include <stdio.h>

#define EQUIPA_FIFO "equipa%d"

struct jogador{
	char nome[20];
	int pontos;
};

struct equipa{
	int pid;
	int fd_equipa;
	char nome[20];
	struct jogador jogadores[12];
};

struct equipa equipas[4];
struct jogador mvp;
int campeonato_a_decorrer = 0;

void campeonato(int fd, char fifo_name[10]){
	int readF = read(fd, &buffer, sizeof(buffer));
	if(readF == -1){
		printf("[ERROR] reading fifo\n");
		close(fd);
		unlink(fifo_name);
		exit(0);
	}

	char nome[10];

	if(sscanf(buffer, "<ponto> %s", nome) == 1){
		for(int i = 0; i < 4; i++){
                        	for(int j = 0; j < 12; j++){
                                	if(strcmp(equipas[i].jogadores[j].nome, buffer) == 0){
                                        	equipas[i].jogadores[j].pontos++;
                                	}
                        	}
                	}
		}
	}
}

int main(int argc, char **argv){
	fifo_name[10];

	if(getenv("GESTORNP") != NULL){
		fifo_name = getenv("GESTORNP");
	} else {
		return 0;
	}

	fd_set read_fd;
	struct timeval tv;

	int fd_gestor, fd_equipa, select_gestor;
	int count = 0;

	if(mkfifo(fifo_name ,0777) == -1){
		printf("[ERROR] creating fifo %s\n", fifo_name);
		return 0;
	}

        while(count < 4){
		struct equipa team;
		fd_gestor = open(fifo_name, O_RDONLY | O_NONBLOCK);
        	if(fd_gestor == -1){
        	        printf("[ERROR] opening fifo %s\n", fifo_name);
	                unlink(fifo_name);
                	return 0;
        	}

                int readC = read(fd, &team, sizeof(team));
                if(readC == -1){
                        printf("[ERROR] reading fifo %s\n", fifo_name);
                	close(fd_gestor);
			unlink(fifo_name);
			return 0;
		}
                equipas[count++] = team;
		close(fd_gestor);
        }

	// (FALTOU A LÓGICA ALEATÓRIA)
	for(int i = 0; i < 4; i + 2){
		char fifo[10];
		sprintf(fifo, EQUIPA_FIFO, equipas[i].pid);

		struct equipa adv = equipas[i + 1];

		int fd_equipa = open(fifo, O_WRONLY | O_NONBLOCK);
		if(fd_equipa == -1){
			printf("[ERROR] opening fifo %s\n", fifo);
			close(fd_gestor);
                        unlink(fifo_name);
			return 0;
		}

		if(i != 3){
			int writeF = write(fd_equipa, &adv, sizeof(adv));
			if(writeF == -1){
                        	printf("[ERROR] opening fifo %s\n", fifo);
                        	close(fd_equipa)
				close(fd_gestor);
                        	unlink(fifo_name);
                        	return 0;
                	}
		} else if(i == 3){
			char buffer[10] = "START!";
			int writeF = write(fd_equipa, &buffer, sizeof(buffer));
                        if(writeF == -1){
                                printf("[ERROR] opening fifo %s\n", fifo);
                                close(fd_equipa)
                                close(fd_gestor);
                                unlink(fifo_name);
                                return 0;
                        }
		}
		close(fd_equipa);
	}

	if(count == 4){
                campeonato_a_decorrer = 1;
        }

	fd_gestor = open(fifo_name, O_RDWR);
        if(fd_gestor == -1){
               printf("[ERROR] opening fifo %s\n", fifo_name);
               unlink(fifo_name);
	       return 0;
        }

	while(campeonato_a_decorrer = 1){
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		FD_ZERO(&read_fd);
		FD_SET(fd_gestor, &read_fd);
		FD_SET(0, &read_fd);

		select_gestor = select(fd_gestor + 1, &read_fd, NULL, NULL, &tv);
		if(select_gestor == -1){
			printf("[ERROR] select\n");
			close(fd_gestor);
			unlink(fifo_name);
			return 0;
		}

		if(select_gestor == 0){
			printf("[WAITING]\n");
			fflush(stdout);
			continue;
		}

		if(FD_ISSET(fd_gestor, &read_fd)){
			campeonato(fd_gestor, fifo_name);
			// FALTA AVISAR AS EQUIPAS.
		}

		if(FD_ISSET(0, &read_fd)){
			char comando[10];
		        scanf("%s", &comando);

        		struct jogador mvp = equipas[0].jogadores[0];

        		if(strcmp(comando, "encerra") == 0){
                		campeonato_a_decorrer = 0;
        		} else if(strcmp(comando, "ponto") == 0){
                		for(int i = 0; i < 4; i++){
                        		for(int j = 0; j < 12; j++){
                                		if(equipas[i].jogadores[j].pontos > mvp.pontos){
                                        		mvp = equipas[i].jogadores[j];
                                		}
                        		}
                		}
                		printf("%s | %d", mvp.nome, mvp.pontos);
        		}
		}
	}

	return 0;
}


#include "funcoes.h"

pthread_mutex_t mutex;

void leComando(char *command, size_t commandSize){
    fgets(command, commandSize, stdin);
    command[strcspn(command, "\n")] = 0;
}

void syncPlayers(ArrayJogadores *players, Map *map, int *isGameRunning, int *currentLevel) {
    for(int i = 0; i < players->nPlayers; ++i) {
        MensagemJogadores packetSender;
        packetSender.type = SYNC;
        packetSender.data.syncPacket.players = *players;
        packetSender.data.syncPacket.map = *map;
        packetSender.data.syncPacket.isGameRunning = *isGameRunning;
        packetSender.data.syncPacket.currentLevel = *currentLevel;
        escrevePIPE(players->playerFd[i], &packetSender, sizeof(MensagemJogadores));
    }
}

int geraAleatorio(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void inicializarBMOV(Keyboard *packet, Bmov *bmov){
    Map *map = packet->map;
    int x;
    int y;
    do {
        x = geraAleatorio(0, MAX_WIDTH - 2);
        y = geraAleatorio(0, MAX_WIDTH - 2);
        if(x % 2 != 0 || y % 2 != 0) {
            continue;
        }
    } while(map->array[x][y] != ' ');
    
    bmov->x = x;
    bmov->y = y;
}

int trataComando(Keyboard *packet, char *input){
    char command[COMMAND_BUFFER_SIZE];
    char arg1[COMMAND_BUFFER_SIZE];

    int numArgs = sscanf(input, "%s %s", command, arg1);

    if (!strcmp(command, "users") && numArgs == 1) {
		 printf("\n[CMD] Lista de Users:\n");
        for(int i = 0; i < packet->players->nPlayers; ++i){
            printf("\t<%s>\n", packet->players->array[i].name);
        }
    } else if(!strcmp(command, "begin") && numArgs == 1) {
        printf("\n[CMD] Jogo esta prestes a comecar!");
        packet->keyboardFeed = 0;
    } else if(!strcmp(command, "kick") && numArgs == 2) {
        printf("\n[CMD] Expulsar: %s\n", packet->players->array->name);
        for(int i = 0; i < packet->players->nPlayers; ++i) {
            if(!strcmp(packet->players->array[i].name, packet->players->array->name)) {
                MensagemJogadores packetSender;
                packetSender.type = KICK;
                strcpy(packetSender.data.content, "\n[CMD] Voce foi expulso pelo motor!\0");
                int fd = pipeWRONLY(packet->players->array[i].pipe);
                escrevePIPE(fd, &packetSender, sizeof(MensagemJogadores));
                close(fd);
                packet->players->array[i] = packet->players->array[packet->players->nPlayers - 1];
                packet->players->playerFd[i] = packet->players->playerFd[packet->players->nPlayers - 1];
                packet->players->nPlayers--;
                MensagemJogadores msg;
                msg.type = MESSAGE;
                char message[100];
                sprintf(message, "\n[CMD] O jogador %s foi expulso do jogo!\0", packet->players->array->name);
                strcpy(msg.data.content, message);
                for(int i = 0; i < packet->players->nPlayers; ++i) {
                    escrevePIPE(packet->players->playerFd[i], &msg, sizeof(MensagemJogadores));
                }
                syncPlayers(packet->players, packet->map, packet->isGameRunning, packet->currentLevel);
            return;
        }
    }
    } else if(!strcmp(command, "end") && numArgs == 1) {
        MensagemJogadores packetSender;
        packetSender.type = END;
        strcpy(packetSender.data.content, "\n[CMD] O jogo foi terminado!\0");
        for(int i = 0; i < packet->players->nPlayers; ++i) {
            escrevePIPE(packet->players->playerFd[i], &packetSender, sizeof(MensagemJogadores));
        }
        close(*packet->motorFd);
        unlink(MOTOR);
        exit(0);
    } else if(!strcmp(command, "bots") && numArgs == 1) {
        ArrayBots *bots = packet->bots;
        for(int i = 0; i < bots->nBots; ++i) {
            printf("[CMD] Intervalo Bots: %d | Duracao Bots: %d\n", bots->bots[i].interval, bots->bots[i].duration);
        }
    } else if(!strcmp(command, "bmov") && numArgs == 1) {
        ArrayBmov *bmovs = packet->bmovs;
        if(bmovs->nbmovs < MAX_BMOVS) {
            pthread_mutex_lock(&mutex);
            inicializarBMOV(packet, &bmovs->bmovs[bmovs->nbmovs]);
            bmovs->nbmovs++;
            printf("\n[CMD] Bmov adicionado!\n");
            pthread_mutex_unlock(&mutex);
        } else {
            printf("\n[CMD] Numero maximo de bloqueios!\n");
        return;
        }
    } else if(!strcmp(command, "rbm") && numArgs == 1) {
        ArrayBmov *bmovs = packet->bmovs;
        if(bmovs->nbmovs <= 0) {
            printf("\n[CMD] Nao ha bloqueios para remover!\n");
        return;
        }
        pthread_mutex_lock(&mutex);
        for(int i = 0; i < bmovs->nbmovs - 1; ++i) {
            bmovs->bmovs[i] = bmovs->bmovs[i + 1];
        }
        bmovs->nbmovs--;
        pthread_mutex_unlock(&mutex);
        printf("\n[CMD] Bmov removido!\n");
    } else if(!strcmp(command, "listBmovs") && numArgs == 1) {
        for(int j=0;j<3;j++) {
            sleep(1);
            for(int i=0;i<packet->bmovs->nbmovs; i++) {
            printf("\n[CMD] Bot %d:%d:%d\n", i+1, packet->bmovs->bmovs[i].x, packet->bmovs->bmovs[i].y);        
            }
        }
    }
    return 1;
}

void *trataTeclado(void *args){   // KeyboardHandlerThread
    Keyboard *packet = (Keyboard*)args;
    char commandBuffer[COMMAND_BUFFER_SIZE];
    while(1) {
        leComando(commandBuffer, sizeof(commandBuffer));
        trataComando(packet, commandBuffer);
    }
} 

void exitJogo(ArrayJogadores *players, const char *name) {
    int *nPlayers = &players->nPlayers;
    
    for(int i = 0; i < *nPlayers; ++i) {
        if(!strcmp(name, players->array[i].name)) {
            (*nPlayers)--;
            players->array[i] = players->array[*nPlayers];
            players->playerFd[i] = players->playerFd[*nPlayers];
            return;
        }
    }
}

void *trataEvento(void *args){  
    Keyboard *packet =(Keyboard*)args;
    ArrayJogadores *players = packet->players;
    int motorFd = *packet->motorFd;

    MensagemJogadores typePacket;
    while(1) {
        lePIPE(motorFd, &typePacket, sizeof(MensagemJogadores));
        switch(typePacket.type) {
            case EXIT:
                exitJogo(players, typePacket.data.content);
                char message[100];
                sprintf(message, "\n[CMD] Jogador %s saiu do jogo!", typePacket.data.content);
                printf("%s\n", message);
                MensagemJogadores msg;
                msg.type = MESSAGE;
                strcpy(msg.data.content, message);
                pthread_mutex_lock(&mutex);
                for(int i = 0; i < players->nPlayers; ++i) {
                    escrevePIPE(players->playerFd[i], &msg, sizeof(msg));
                }
                pthread_mutex_unlock(&mutex);
                break;

            case UPDATE_POS:
                pthread_mutex_lock(&mutex);
                pid_t playerPid = typePacket.data.player.pid;
                for(int i = 0; i < packet->players->nPlayers; ++i) {
                    if(playerPid == packet->players->array[i].pid) {
                        packet->map->array[packet->players->array[i].yCoordinate][packet->players->array[i].xCoordinate] = ' ';
                        packet->players->array[i].xCoordinate = typePacket.data.player.xCoordinate;
                        packet->players->array[i].yCoordinate = typePacket.data.player.yCoordinate;
                        packet->map->array[typePacket.data.player.yCoordinate][typePacket.data.player.xCoordinate] = packet->players->array[i].icone;
                    }
                }
                pthread_mutex_unlock(&mutex);
                break;

            case PLAYER_JOIN:
                int conf = 0;
                typePacket.data.player.isPlaying = 0;
                pthread_mutex_lock(&mutex);
                players->array[players->nPlayers] = typePacket.data.player;
                sprintf(players->array[players->nPlayers].name, "\n[CMD] Spectator %d!", players->nPlayers);
                players->array[players->nPlayers].icone = ' ';
                int newPlayerFd = pipeWRONLY(players->array[players->nPlayers].pipe);
                players->playerFd[players->nPlayers] = newPlayerFd;
                players->nPlayers++;
                pthread_mutex_unlock(&mutex);
                escrevePIPE(newPlayerFd, &conf, sizeof(int));
                MensagemJogadores msg1;
                msg1.type = MESSAGE;
                sprintf(msg1.data.content, "\n[CMD] %s entrou!\0\n", players->array[players->nPlayers - 1].name);
                for(int i = 0; i < players->nPlayers; ++i) {
                    if(players->array[i].pid != players->array[players->nPlayers - 1].pid) {
                        escrevePIPE(players->playerFd[i], &msg1, sizeof(MensagemJogadores));
                    }
                }
                break;
        }
        syncPlayers(players, packet->map, packet->isGameRunning, packet->currentLevel);
        for(int i = 0; i < packet->players->nPlayers; ++i) {
            if(packet->players->array[i].yCoordinate == 0 && packet->players->array[i].xCoordinate > 1) {
                printf("\n[CMD] Jogador %s ganhou o jogo!!\0\n", packet->players->array[i].name);
                *packet->isGameRunning = 0;
                MensagemJogadores win;
                win.type = PLAYER_WON;
                strcpy(win.data.content, packet->players->array[i].name);
                for(int j = 0; j < packet->players->nPlayers; ++j) {
                    escrevePIPE(packet->players->playerFd[j], &win, sizeof(MensagemJogadores));
                }
            }
        }
    }
}

void adicionaBOT(Keyboard *packet, int interval, int duration) {
    ArrayBots *bots = packet->bots;

    if(bots->nBots < MAX_BOTS) {
        bots->bots[bots->nBots].interval = interval;
        bots->bots[bots->nBots].duration = duration;
        bots->nBots++;
    }
}

void inicializarBOT(Keyboard *packet){
    printf("\n[CMD] Bots vao comecar!\n");  
    ArrayBots *bots = packet->bots;
    int pipe_fd[2];
    if(pipe(pipe_fd) == -1){
    	perror("[ERROR] PIPE BOT");
        exit(0);
    }
    for(int i = 0; i < bots->nBots; ++i) {
        pid_t pid2 = fork();
        if(!pid2) {
            char intervalBuffer[3];
            sprintf(intervalBuffer, "%d", bots->bots[i].interval);
            char durationBuffer[3];
            sprintf(durationBuffer, "%d", bots->bots[i].duration);
            char frase[20];
            close(pipe_fd[0]); 
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
            execlp("./bot", "./bot", intervalBuffer, durationBuffer, NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
    }
    
    close(pipe_fd[1]);
    char buffer[256];
    ssize_t bytesRead;  
    while (*packet->isGameRunning) {
        bytesRead = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead > 0 && *packet->isGameRunning) {
            buffer[bytesRead] = '\0'; 
            printf("\n[CMD] Recebido: %s\n", buffer); fflush(stdout);
            sscanf(buffer, "%d %d %d", &packet->map->stones[packet->map->currentStones].x, 
                                        &packet->map->stones[packet->map->currentStones].y, 
                                        &packet->map->stones[packet->map->currentStones].duration);
            packet->map->stones[packet->map->currentStones].x *= 2;
            packet->map->currentStones++;
            for(int i = 0; i < packet->map->currentStones; ++i) {
                packet->map->array[packet->map->stones[i].y][packet->map->stones[i].x] = 'P';
                printf("\n[CMD] %d: %d, %d\n", i, packet->map->stones[i].x, packet->map->stones[i].y);
            }
            syncPlayers(packet->players, packet->map, packet->isGameRunning, packet->currentLevel);
        }
    }
    printf("\n[CMD] Bots a terminar!\n");
    packet->map->currentStones = 0;
    packet->bots->nBots = 0;
    close(pipe_fd[0]); 
    wait(NULL);
}

void *trataBOT(void *args){    
    Keyboard *packet = (Keyboard*)args;
    ArrayBots *bots = packet->bots;
    int currentLevel = *packet->currentLevel;
    pthread_t botsThread;
    
    switch(currentLevel) {
        case 1:
            adicionaBOT(packet, 30, 10);
            adicionaBOT(packet, 25, 5);
            break;

        case 2:
            adicionaBOT(packet, 30, 15);
            adicionaBOT(packet, 25, 10);
            adicionaBOT(packet, 20, 5);
            break;

        case 3:
            adicionaBOT(packet, 30, 20);
            adicionaBOT(packet, 25, 15);
            adicionaBOT(packet, 20, 10);
            adicionaBOT(packet, 15, 5);
            break;
    }
    inicializarBOT(packet);
}     

int verificaPosBMOV(ArrayJogadores *players, int currentX, int currentY, Map *map) {
    for(int i = 0; i < players->nPlayers; ++i) {
        if(currentX == players->array[i].xCoordinate && currentY == players->array[i].yCoordinate) {
            return 0;
        }
    }

    if(currentX < 1 || currentY < 1 || currentX > MAX_WIDTH || currentY > MAX_HEIGHT) {
        return 0;
    }

    if(map->array[currentY][currentX] == '#') {
        return 0;
    }

    return 1;
}

void movimentoBMOV(Bmov *bmov, ArrayJogadores *players, Map *map) {
    int isValidPosition = 1;
    int currentX = bmov->x, currentY = bmov->y;
    do {
        int side = rand() % 4 + 1;
        switch(side) {
            case 1:
                currentX += 2;
                break;
            case 2:
                currentX -= 2;
                break;
            case 3:
                currentY++;
                break;
            case 4:
                currentY--;
                break;
            default:
                printf("\n[CMD] rand invalido");
                break;
        }
        isValidPosition = verificaPosBMOV(players, currentX, currentY, map);
    }while(!isValidPosition);

    bmov->x = currentX;
    bmov->y = currentY;
}

void *trataBMOVS(void *args){
    printf("\n[CMD] Bmovs vao comecar!\n");
    Keyboard *packet = (Keyboard*)args;
    ArrayBmov *bmovs = packet->bmovs;
    ArrayJogadores *players = packet->players;
    Map *map = packet->map;
    while(*packet->isGameRunning) { //  todo: adicionar mutex
        sleep(1);
        for(int i = 0; i < bmovs->nbmovs; ++i) {
            map->array[bmovs->bmovs[i].y][bmovs->bmovs[i].x] = ' ';
            movimentoBMOV(&bmovs->bmovs[i], players, map);
            map->array[bmovs->bmovs[i].y][bmovs->bmovs[i].x] = 'B';
        }
        syncPlayers(players, map, packet->isGameRunning, packet->currentLevel);
    }
    bmovs->nbmovs = 0;
    printf("\n[CMD] Terminou os bmovs!\n");
}

void* trataPedras(void* args){
    Keyboard *packet = (Keyboard*)args;
    while(*packet->isGameRunning) {
        for(int i = 0; i < packet->map->currentStones; ++i) {
            printf("\n[CMD] Duracao Pedra: %d\n", packet->map->stones[i].duration);
            if(packet->map->stones[i].duration == 0) {
                int currentStoneX = packet->map->stones[i].x;
                int currentStoneY = packet->map->stones[i].y;
                packet->map->array[currentStoneY][currentStoneX] = ' ';
                packet->map->stones[i] = packet->map->stones[packet->map->currentStones - 1];
                packet->map->currentStones--;
                printf("\n[CMD] Pedra apagada!\n");
            } else {
                packet->map->stones[i].duration--;
            }
        }
        sleep(1);
    }
}

void getEnvs(int* inscricao, int* nplayers, int* duracao, int* decremento) {
    if(getenv("INSCRICAO") == NULL || getenv("NPLAYERS") == NULL || getenv("DURACAO") == NULL || getenv("DECREMENTO") == NULL) {
        printf("\n[CMD] Variaveis de ambiente nao se encontram inicializadas!\n");
        exit(1);
    }
    *inscricao = atoi(getenv("INSCRICAO"));
    *nplayers = atoi(getenv("NPLAYERS"));
    *duracao = atoi(getenv("DURACAO"));
    *decremento = atoi(getenv("DECREMENTO"));
}

void setupSigIntMotor() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sairMotor;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    if (sigaction(SIGINT, &sigIntHandler, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void inicializarMotor(int *motorFd, int *inscricao, int *nplayers, int *duracao, int *decremento) {
    srand(time(NULL)); 
    getEnvs(inscricao, nplayers, duracao, decremento);
    setupSigIntMotor();
    if(mkfifo(MOTOR, 0666) == -1) {
        perror("Creating Pipe");
        exit(EXIT_FAILURE); 
    }
    *motorFd = pipeRDWR(MOTOR);
}

void inicializarLocJogadores(Keyboard *packet){
    ArrayJogadores *players = packet->players;
    Map *map = packet->map;

    int startingRow = MAX_HEIGHT - 1;

    for(int i = 0; i < players->nPlayers; ++i) {
        if(players->array[i].isPlaying == 0) {
            continue;
        }

        int randomX = 0;
        int icone = players->array[i].icone;
        players->array[i].yCoordinate = startingRow;
        do {
            randomX = geraAleatorio(0, MAX_WIDTH - 2);
        } while(map->array[startingRow][randomX] != ' ');
        players->array[i].xCoordinate = randomX;
        map->array[startingRow][randomX] = icone;
    }
}

void inicializarSYNC(ArrayJogadores *players, Map *map, int *isGameRunning, int *currentLevel){
    JogadorNivel syncPacket = {*players, *map, *isGameRunning, *currentLevel};
    MensagemJogadores packet;
    packet.type = SYNC;
    packet.data.syncPacket = syncPacket;
    for(int i = 0; i < players->nPlayers; ++i) {
        players->playerFd[i] = pipeWRONLY(players->array[i].pipe);
        escrevePIPE(players->playerFd[i], &packet, sizeof(MensagemJogadores));
    }
}


void comecaBOTS(Keyboard *packet, pthread_t *threadId) {
    if(pthread_create(threadId, NULL, trataBOT, (void*)packet) != 0) {
        perror("\n[ERROR] Creating thread");
        exit(EXIT_FAILURE);
    } 
}

void comecaBMOVS(Keyboard *packet, pthread_t *threadId) {
    if(pthread_create(threadId, NULL, trataBMOVS, (void*)packet) != 0) {
        perror("\n[ERROR] Creating thread");
        exit(EXIT_FAILURE);
    }
}

void comecaPedras(Keyboard *packet, pthread_t *threadId) {
    if(pthread_create(threadId, NULL, trataPedras, (void*)packet) != 0) {
        perror("\n[ERROR] Creating thread");
        exit(EXIT_FAILURE);
    }
}

void comecaTeclado(Keyboard *packet, pthread_t *threadId) {
    if(pthread_create(threadId, NULL, trataTeclado, (void*)packet) != 0) {
        perror("\n[ERROR] Creating thread");
        exit(EXIT_FAILURE);
    }
}

void comecaEventos(Keyboard *packet, pthread_t *threadId) {
    if(pthread_create(threadId, NULL, trataEvento, (void*)packet) != 0) {
        perror("\n[ERROR] Creating thread");
        exit(EXIT_FAILURE);
    }
}

int verificaNome(const ArrayJogadores *players, const char *name){
    for(int i = 0; i < players->nPlayers; ++i) {
        if(!strcmp(name, players[i].array->name)) {
            return 0;
        }
    }
    return 1;
}


void leMapa(Map *map, const char *filename) {
    memset(&map->array, 0, sizeof(map->array));
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < MAX_HEIGHT; ++i) {
        for(int j = 0; j < MAX_WIDTH; ++j) {
            int nRead = read(fd, &map->array[i][j], sizeof(char));
        }
    }
    
    close(fd);
}

void getPlayer(ArrayJogadores *players, int motorFd) {
    int confirmationFlag = 0;
    MensagemJogadores reg = {0};
    lePIPE(motorFd, &reg, sizeof(MensagemJogadores));
    players->array[players->nPlayers] = reg.data.player;
    int currentjogoUIFd = pipeWRONLY(players->array[players->nPlayers].pipe);
    if (verificaNome(players, players->array[players->nPlayers].name)) {
        players->array[players->nPlayers].isPlaying = 1;
        confirmationFlag = 1;
        escrevePIPE(currentjogoUIFd, &confirmationFlag, sizeof(int));
    } else {
        sprintf(players->array[players->nPlayers].name, "\n[CMD] Espetador %d!", players->nPlayers);
        players->array[players->nPlayers].icone = ' ';
        escrevePIPE(currentjogoUIFd, &confirmationFlag, sizeof(int));
    }

    players->nPlayers++;
    close(currentjogoUIFd);
}

void playerLobby(Keyboard *keyboardPacket, int inscricao, int nplayers) {
    ArrayJogadores *players = keyboardPacket->players;
    int motorFd = *keyboardPacket->motorFd;
    
    fd_set readFds;
    FD_ZERO(&readFds);
    FD_SET(motorFd, &readFds);

    time_t startTime, currentTime;
    time(&startTime);

    while(keyboardPacket->keyboardFeed && players->nPlayers < MAX_PLAYERS) {
        time(&currentTime);
        double timeElapsed = difftime(currentTime, startTime);
        double timeRemaining = inscricao - timeElapsed;
        
        struct timeval timeout;
        if(timeRemaining < 0) {
            timeRemaining = 0;
        }
        timeout.tv_sec = (int)timeRemaining;
        timeout.tv_usec = 0;
        printf("\n[CMD] %d\n", (int)timeout.tv_sec);
        int ready = select(motorFd + 1, &readFds, NULL, NULL, &timeout);

        switch(ready) {
            case -1:
                perror("\n[ERROR] Select");
                exit(0);

            case 0:
                if(players->nPlayers >= nplayers) {
                    return;
                } else {
                    while(players->nPlayers < nplayers) {
                        getPlayer(players, motorFd);
                    }
                    return;
                }

            default:
                if(FD_ISSET(motorFd, &readFds)) {
                    getPlayer(players, motorFd);
                }
                break;
        }
    }
}

void setupCommand(WINDOW* windowComandos) {
    echo();
    curs_set(2);
    wmove(windowComandos, 2, 2);
}

void comandoEND(Keyboard *packet) {
    MensagemJogadores packetSender;
    packetSender.type = END;
    strcpy(packetSender.data.content, "\n[CMD] O jogo foi terminado!\0");
    for(int i = 0; i < packet->players->nPlayers; ++i) {
        escrevePIPE(packet->players->playerFd[i], &packetSender, sizeof(MensagemJogadores));
    }
    close(*packet->motorFd);
    unlink(MOTOR);
    exit(0);
}



int main(int argc, char* argv[]) {  
    
    int inscricao = 0, nplayers = 0, duracao = 0, decremento = 0; 
    int motorFd = 0, currentLevel = 1, isGameRunning = 0; 
    int tempo = 0;
    ArrayJogadores players = {};
    Map map = {}; 
    ArrayBots bots = {}; 
    ArrayBmov bmovs = {}; 
    Keyboard keyboardPacket = {&players, &map, &bots, &bmovs, 1, &motorFd, NULL, &isGameRunning, &currentLevel};
    pthread_t keyBoardHandlerThread, eventHandlerThread, botHandlerThread, bmovHandlerThread, stonesHandlerThread;

    inicializarMotor(&motorFd, &inscricao, &nplayers, &duracao, &decremento);
    
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("\n[CMD] Inicializacao mutex falhou.\n");
        return 1;
    }

    comecaTeclado(&keyboardPacket, &keyBoardHandlerThread);

    playerLobby(&keyboardPacket, inscricao, nplayers);

    comecaEventos(&keyboardPacket, &eventHandlerThread);

    while(currentLevel < 4) {
        isGameRunning = 1;
        printf("\n[CMD] Nivel: %d\n", currentLevel);
        char mapBuffer[100];
        sprintf(mapBuffer, "maze%d.txt", currentLevel);
        printf("\n[CMD] Mapa: %s\n", mapBuffer);
        leMapa(&map, mapBuffer); //depois temos de mudar consoante o nivel
        printf("\n[CMD] Leu mapa de jogo do ficheiro!\n");
        inicializarLocJogadores(&keyboardPacket);
        printf("\n[CMD] Jogadores Inicializados\n");
        inicializarSYNC(&players, &map, &isGameRunning, &currentLevel);
        comecaBOTS(&keyboardPacket, &botHandlerThread);
        comecaPedras(&keyboardPacket, &stonesHandlerThread);
        comecaBMOVS(&keyboardPacket, &bmovHandlerThread);
        tempo = duracao - decremento * (currentLevel - 1);

        while(isGameRunning && tempo != 0) {
            sleep(1);
            tempo--;
            printf("\n[CMD] Tempo restante: %d!\n", tempo);
        }
        MensagemJogadores msg;
        msg.type = MESSAGE;
        sprintf(msg.data.content, "\n[CMD] Nivel %d terminado, aguarde!", currentLevel);
        for(int i = 0; i < keyboardPacket.players->nPlayers; ++i) {
            escrevePIPE(keyboardPacket.players->playerFd[i], &msg, sizeof(MensagemJogadores));
        }
        currentLevel++;
        isGameRunning = 0;
        pthread_join(bmovHandlerThread, NULL);
        pthread_join(botHandlerThread, NULL);
        pthread_join(stonesHandlerThread, NULL);
        printf("\n[CMD] Jogo devia terminar!\n");
    }

    comandoEND(&keyboardPacket);    
    if (pthread_join(keyBoardHandlerThread, NULL) != 0) {
        perror("Join thread");
        return EXIT_FAILURE;
    }

    pthread_mutex_destroy(&mutex);

    unlink(MOTOR);
    return 0;
}

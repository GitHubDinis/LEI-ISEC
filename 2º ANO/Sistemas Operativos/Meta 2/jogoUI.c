#include "funcoes.h"

void inicializaJogoUI(Jogador* player, const int argc, char* argv[]);
void inicializaJogador(Jogador* player, const int argc, char* argv[]);
void registaJogador(int *motorFd, int *jogoUIFd, Jogador *player);
void *trataTeclado(void *args);
void leComando(char *command, size_t commandSize);
int trataComando(char *input, Keyboard *packet);
void comandoMSG(Keyboard *packet, char *arg1, char *arg2);
void comandoPLAYERS(Keyboard *packet);
int devolveLocalizacao(Keyboard *packet);
void comandoEXIT(Keyboard *packet);
void *trataEventos(void *args);
void comecaEvento(Keyboard *packet, pthread_t *threadId);
int verificaPosicao(Keyboard *packet, int direction);

void inicializaEcra() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

WINDOW *windowJogo;
WINDOW *windowComandos;

int main(int argc, char* argv[]) {
    Jogador player = {}; 
    ArrayJogadores players = {};
    Map map = {};
    int jogoUIFd, motorFd;
    int isGameRunning = 0, currentLevel = 1;
    Keyboard keyboardPacket = {&players, &map, NULL, NULL, 1, &motorFd, &jogoUIFd, &isGameRunning, &currentLevel};
    pthread_t eventHandler;

    inicializaJogoUI(&player, argc, argv);

    registaJogador(&motorFd, &jogoUIFd, &player);

    comecaEvento(&keyboardPacket, &eventHandler);

    sleep(6);
    inicializaEcra();

    windowJogo = newwin(18, 82, 1, 1);
    windowComandos = newwin(10, 60, 19, 1);

    box(windowJogo, 0, 0);
    box(windowComandos, 0, 0);
    refresh();

    wrefresh(windowJogo);
    wrefresh(windowComandos);

    while(currentLevel < 4) {
        while(isGameRunning) {
            int key;
            while((key = getch())) {
                int canGo;
                if(key==KEY_UP || key==KEY_DOWN || key==KEY_LEFT || key == KEY_RIGHT) {
                    canGo=verificaPosicao(&keyboardPacket, key);
                }
                switch(key) {
                    case KEY_UP:
                        if(!canGo) {
                            players.array[devolveLocalizacao(&keyboardPacket)].yCoordinate--;
                        }
                        break;

                    case KEY_DOWN:
                       if(!canGo) {
                            players.array[devolveLocalizacao(&keyboardPacket)].yCoordinate++;
                        }
                        break;

                    case KEY_LEFT:
                        if(!canGo) {
                            players.array[devolveLocalizacao(&keyboardPacket)].xCoordinate -= 2;
                        }
                        break;

                    case KEY_RIGHT:
                        if(!canGo) {
                            players.array[devolveLocalizacao(&keyboardPacket)].xCoordinate += 2;
                        }
                        break;

                    case 32:
                        char commandBuffer[COMMAND_BUFFER_SIZE];
                        mvwprintw(windowComandos, 7, 1, "%s" ,"-->");
                        leComando(commandBuffer, sizeof(commandBuffer));
                        trataComando(commandBuffer, &keyboardPacket);
                }
                if(player.isPlaying) {
                    int myPos = devolveLocalizacao(&keyboardPacket);
                    MensagemJogadores move;
                    move.type = UPDATE_POS;
                    move.data.player = keyboardPacket.players->array[myPos];
                    escrevePIPE(*keyboardPacket.motorFd, &move, sizeof(MensagemJogadores));
                    wrefresh(windowJogo);
                    wrefresh(windowComandos);
                }
                
            }
        }
        wclear(windowComandos);
        box(windowComandos, 0, 0);
    }



    if(pthread_join(eventHandler, NULL) != 0) {
        perror("Join thread");
        return EXIT_FAILURE;
    }
    
    close(motorFd);
    close(jogoUIFd);
    unlink(player.pipe);
    return 0;
}

int verificaPosicao(Keyboard *packet, int direction) {

    int myX, myY;
    myX = packet->players->array[devolveLocalizacao(packet)].xCoordinate;
    myY = packet->players->array[devolveLocalizacao(packet)].yCoordinate;
    
    switch(direction) {
        case KEY_UP:
            myY--;
            break;
        case KEY_DOWN:
            myY++;
            break;
        case KEY_LEFT:
            myX -= 2;
            break;
        case KEY_RIGHT:
            myX += 2;
            break;
        default:
            exit(1);
            
    }
    if(packet->map->array[myY][myX]==' ') {
        return 0;
    } return 1;
    
    //0 se sim 1 se nao
}

void comecaEvento(Keyboard *packet, pthread_t *threadId) {
    if(pthread_create(threadId, NULL, trataEventos, (void*)packet)) {
        perror("Creating thread");
        exit(EXIT_FAILURE);
    }
}


void printMap(WINDOW *mapWindow, Map *map) {
    for (int i = 0; i < MAX_HEIGHT; ++i) {
        for (int j = 0; j < MAX_WIDTH; ++j) {
            if(map->array[i][j] != '\n')
                mvwaddch(mapWindow, i + 1, j + 1, map->array[i][j]); 
        }
    }
    wrefresh(mapWindow);
}

void *trataEventos(void *args) {
    Keyboard *eventPacket = (Keyboard*)args;
    MensagemJogadores packet;
    while(1) {
        int myId = devolveLocalizacao(eventPacket);
        lePIPE(*(eventPacket->jogoUIFd), &packet, sizeof(MensagemJogadores));
        switch(packet.type) {
            case KICK:
                wclear(windowComandos);
                box(windowComandos, 0, 0);
                mvwprintw(windowComandos, 1, 1, "%s\n", packet.data.content);
                wrefresh(windowComandos);
                sleep(5);
                close(*(eventPacket->motorFd));
                close(*(eventPacket->jogoUIFd));
                unlink(eventPacket->players->array[myId].pipe);
                exit(0);

            case MESSAGE:
                wclear(windowComandos);
                box(windowComandos, 0, 0);
                mvwprintw(windowComandos, 1, 1, "%s", packet.data.content);
                wrefresh(windowComandos);
                break;

            case SYNC:
                *(eventPacket->players) = packet.data.syncPacket.players;
                *(eventPacket->map) = packet.data.syncPacket.map;
                *(eventPacket->currentLevel) = packet.data.syncPacket.currentLevel;
                *(eventPacket->isGameRunning) = packet.data.syncPacket.isGameRunning;
                printMap(windowJogo, eventPacket->map);
                break;
            
            case END:
                wclear(windowComandos);
                box(windowComandos, 0, 0);
                mvwprintw(windowComandos, 1, 1, "%s\n", packet.data.content);
                wrefresh(windowComandos);
                sleep(2);
                close(*eventPacket->motorFd);
                close(*eventPacket->jogoUIFd);
                unlink(eventPacket->players->array[myId].pipe);
                exit(0);

            case PLAYER_WON:
                wclear(windowComandos);
                box(windowComandos, 0, 0);
                mvwprintw(windowComandos, 1, 1, "O jogador %s ganhou!\n", packet.data.content);                
                mvwprintw(windowComandos, 2, 1, "O proximo nivel vai comecar brevemente");
                wrefresh(windowComandos);
                sleep(5);
                break;

            default:
                break;
        }
    }
}

void registaJogador(int *motorFd, int *jogoUIFd, Jogador *player) {
    int confirmationFlag = 0;
    *motorFd = pipeWRONLY(MOTOR);
    MensagemJogadores reg;
    reg.type = PLAYER_JOIN;
    reg.data.player = *player;
    escrevePIPE(*motorFd, &reg, sizeof(MensagemJogadores));

    *jogoUIFd = pipeRDONLY(player->pipe);
    lePIPE(*jogoUIFd, &confirmationFlag, sizeof(int));
    player->isPlaying = confirmationFlag;
    if(confirmationFlag) {
        printf("O jogo vai comecar dentro de poucos segundos! Esteja pronto para jogar\n");
    } else {
        printf("Oops, ja existe alguem com este nome ou o jogo ja comecou, vai ficar como espetador!\n");
    }
}

void inicializaJogoUI(Jogador* player, const int argc, char* argv[]) {
    inicializaJogador(player, argc, argv);
    if(mkfifo(player->pipe, 0666) == -1) {
        perror("Creating Pipe");
        exit(EXIT_FAILURE); 
    }
}

void inicializaJogador(Jogador* player, const int argc, char* argv[]) {
    if(argc != 2 || strlen(argv[1]) > 12) {
        perror("Getting jogoUI args");
        exit(EXIT_FAILURE);
    }

    strcpy(player->name, argv[1]);
    player->pid = getpid();
    player->xCoordinate = 0;
    player->yCoordinate = 0;
    player->icone = player->name[0];
    sprintf(player->pipe, JOGO, player->pid);
    player->isPlaying = 0;
}

void leComando(char *command, size_t commandSize) {
    echo();
    curs_set(2);
    wmove(windowComandos, 7, 5);
    wgetnstr(windowComandos, command, commandSize);
    noecho();
    curs_set(0);
}

int trataComando(char *input, Keyboard *packet) {
    wclear(windowComandos);
    box(windowComandos, 0, 0);
    wrefresh(windowComandos);
	char command[COMMAND_BUFFER_SIZE];
    char arg1[COMMAND_BUFFER_SIZE], arg2[COMMAND_BUFFER_SIZE];
    int nArgs = sscanf(input, "%s %s %[^\n]", command, arg1, arg2);
    if (!strcmp(command, "msg") && nArgs == 3) {
		comandoMSG(packet, arg1, arg2);
    } else if(!strcmp(command, "players") && nArgs == 1) {
        comandoPLAYERS(packet);
    } else if(!strcmp(command, "exit") && nArgs == 1) {
        comandoEXIT(packet);
    } else {
        mvwprintw(windowComandos, 1, 1, "Comando Invalido\n");
    } 
    return 1;
}

void comandoMSG(Keyboard *packet, char *arg1, char *arg2) {
    for(int i = 0; i < packet->players->nPlayers; ++i) {
        if(!strcmp(packet->players->array[i].name, arg1)) {
            MensagemJogadores packetSender = {MESSAGE};
            char msgBuffer[50];
            sprintf(msgBuffer, "<%s> %s\0", packet->players->array[devolveLocalizacao(packet)].name, arg2);
            strcpy(packetSender.data.content, msgBuffer);
            int fd = pipeWRONLY(packet->players->array[i].pipe);
            escrevePIPE(fd, &packetSender, sizeof(MensagemJogadores));
            close(fd);
        }
    }
}

void comandoPLAYERS(Keyboard *packet) {
    for(int i = 0; i < packet->players->nPlayers; ++i) {
        mvwprintw(windowComandos, i + 1, 1, "Nome | Icone: %s | %c\0\n", packet->players->array[i].name, packet->players->array[i].icone);
    }
}

int devolveLocalizacao(Keyboard *packet) {
    for(int i=0; i<packet->players->nPlayers; i++) {
        if(getpid() == packet->players->array[i].pid) {
            return i;
        }
    }
    return -1;
}

void comandoEXIT(Keyboard *packet) {
    MensagemJogadores packetSender = {EXIT};
    int myId = devolveLocalizacao(packet);
    strcpy(packetSender.data.content, packet->players->array[myId].name);
    escrevePIPE(*packet->motorFd, &packetSender, sizeof(MensagemJogadores));
    close(*packet->motorFd);
    char buffer[20];
    sprintf(buffer, JOGO, getpid());
    unlink(buffer);
    exit(0);
}

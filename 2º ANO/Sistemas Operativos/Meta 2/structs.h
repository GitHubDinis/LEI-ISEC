#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/select.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <ncurses.h>

#define MAX_HEIGHT 16
#define MAX_WIDTH 81
#define MAX_PLAYERS 5
#define MAX_STONES 50
#define MAX_BMOVS 5
#define MAX_BOTS 10
#define COMMAND_BUFFER_SIZE 80
#define MAX_PIPE_SIZE 12

typedef struct {
    char name[12];
    pid_t pid;
    char pipe[MAX_PIPE_SIZE];
    int xCoordinate;
    int yCoordinate;
    char icone;
    int isPlaying;
}Jogador;

typedef struct {
    Jogador array[MAX_PLAYERS];
    int playerFd[MAX_PLAYERS];
    int nPlayers;
} ArrayJogadores;

typedef struct {
    int interval;
    int duration;
    pthread_t *botThread;
} Bot;

typedef struct {
    Bot bots[MAX_BOTS];
    int nBots;
} ArrayBots;

typedef struct {
    int x;
    int y;
} Bmov;

typedef struct {
    Bmov bmovs[MAX_BMOVS];
    int nbmovs;
} ArrayBmov;

typedef struct {
    int x;
    int y;
    int duration;
} Stone;

typedef struct {
    Stone stones[MAX_STONES];
    int currentStones;
    char array[MAX_HEIGHT][MAX_WIDTH];
} Map;

typedef struct {
    ArrayJogadores *players;
    Map *map;
    ArrayBots *bots;
    ArrayBmov *bmovs;
    int keyboardFeed;
    int *motorFd;
    int *jogoUIFd;
    int *isGameRunning;
    int *currentLevel;
} Keyboard;

typedef struct {
    ArrayJogadores players;
    Map map;
    int isGameRunning;
    int currentLevel;
} JogadorNivel;

union Data {
    char content[COMMAND_BUFFER_SIZE];
    JogadorNivel syncPacket;
    Jogador player;
};

typedef enum {KICK,MESSAGE,EXIT,SYNC,END,UPDATE_POS,PLAYER_WON,PLAYER_JOIN} Mensagem;

typedef struct {
    Mensagem type;
    union Data data;
} MensagemJogadores;

typedef struct {
    Keyboard *packet;
    int interval;
    int duration;
} JuntaInfoBot;

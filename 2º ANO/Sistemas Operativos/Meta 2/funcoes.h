#include "structs.h"

#define JOGO "JOGOUI-%d"
#define MOTOR "PIPEMOTOR"

void escrevePIPE(const int fd, void *data, size_t size);
void lePIPE(const int fd, void *data, size_t size);
int pipeRDONLY(const char *pipeName);
int pipeWRONLY(const char *pipeName);
int pipeRDWR(const char *pipeName);
void sairMotor(int signum);

void sairJogoUI(int signum);
void sinalJogoUI();

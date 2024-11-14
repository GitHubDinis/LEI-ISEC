#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define SERVER_FIFO "server_FIFO"
#define CLIENT_FIFO "client_%d_FIFO"

#define TAM_MAX 50

typedef struct{
	pid_t pid_cliente;
	char palavra[TAM_MAX];
} pergunta;

typedef struct{
	char palavra[TAM_MAX];
} resposta;

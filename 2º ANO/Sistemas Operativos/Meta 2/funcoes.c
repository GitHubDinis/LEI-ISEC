#include "funcoes.h"

void escrevePIPE(const int fd, void *data, size_t size) {
    ssize_t bytesWritten;
    while(!(bytesWritten = write(fd, data, size)));
    if (bytesWritten == -1) {
        perror("Writing to Pipe");
        close(fd);
        exit(EXIT_FAILURE);
    }
}

void lePIPE(const int fd, void *data, size_t size) {
    ssize_t bytesRead;
    while(!(bytesRead = read(fd, data, size)));
    if (bytesRead == -1) {
        perror("Reading from Pipe");
        close(fd);
        exit(EXIT_FAILURE);
    }
}

int pipeRDONLY(const char *pipeName) {
    int fd = open(pipeName, O_RDONLY);
    if (fd == -1) {
        perror("Opening Pipe for Reading");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int pipeWRONLY(const char *pipeName) {
    int fd = open(pipeName, O_WRONLY);
    if (fd == -1) {
        perror("Opening Pipe for Writing");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int pipeRDWR(const char *pipeName) {
    int fd = open(pipeName, O_RDWR);
    if(fd == -1) {
        perror("Opening Pipe for Reading/Writing");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void sinalJogoUI() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sairJogoUI;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    if (sigaction(SIGINT, &sigIntHandler, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void sairJogoUI(int signum) {
    char buffer[20];
    sprintf(buffer, JOGO, getpid());
    unlink(buffer);
    exit(0);
}

void sairMotor(int signum) {
    unlink(MOTOR);
    exit(0);
}

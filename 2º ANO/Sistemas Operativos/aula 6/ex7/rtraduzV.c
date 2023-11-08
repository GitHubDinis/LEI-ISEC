#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> // Para a função exit
#include <sys/wait.h>

int main() {
    int fd1[2];
    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(1);
    }

    char opcao, palavra[100];
    printf("\nEscolha o idioma i, f ou x para sair\n");
    scanf(" %c", &opcao); // Adicionei um espaço em branco antes de %c para ignorar espaços em branco extras

    if (opcao == 'x') {
        return 1;
    } else {
        while (getchar() != '\n')
            ; // apanhar lixo

        printf("Introduza a palavra \n");
        fgets(palavra, sizeof(palavra), stdin);
        palavra[strlen(palavra) - 1] = '\0'; // Remova o caractere de nova linha
    }

    pid_t p = fork();

    if (p == 0) {
        if (opcao == 'i') {
            execl("rding", "rding", palavra, NULL);
            perror("execl");
            exit(1);
        } else if (opcao == 'f') {
            close(0);
            dup(fd1[0]);
            close(fd1[0]);
            close(fd1[1]);
            execl("rdfran", "rdfran", NULL);
            perror("execl");
            exit(1);
        }
    } else if (p > 0) {
        if (opcao == 'f') {
            close(fd1[0]);
            int size = write(fd1[1], palavra, strlen(palavra) + 1);
            printf("\nenviou - %d\n", size);
        }
        wait(&p);
    }

    return 1;
}



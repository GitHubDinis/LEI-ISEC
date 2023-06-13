#include <stdio.h>
#include <string.h>

// GUIÃO 4
// EXERCICÍO 1

struct paragem{
    char nome[50];
    int minutos;
};

void mostraFich(char *nome){
    FILE *f;
    struct paragem p;

    f = fopen(nome, "rb");
    if(f == NULL){
        printf("erro no acesso ao fichiero\n");
        return;
    }

    while (fread(&p, sizeof(struct paragem), 1, f) == 1)
        printf("%s: %d\n", p.nome, p.minutos);

    fclose(f);
}

void mostraInicioFim(char *nome){
    FILE *f;
    struct paragem p;

    f = fopen(nome, "rb");
    if(f == NULL){
        printf("erro no acesso ao fichiero\n");
    }

    fread(&p, sizeof(struct paragem), 1, f);
    printf("Primeira: %s: %d\n", p.nome, p.minutos);

    fseek(f, -sizeof(struct paragem),SEEK_END);
    fread(&p, sizeof(struct paragem), 1, f);
    printf("Ultima: %s: %d\n", p.nome, p.minutos);

    fclose(f);
}

int existe(char *nome, char *nome1){
    FILE *f;
    struct paragem p;

    f = fopen(nome, "rb");
    if(f == NULL){
        printf("erro no acesso ao fichiero\n");
    }

    while (fread(&p, sizeof(struct paragem), 1, f) == 1) {
        if (strcmp(p.nome, nome1) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int main() {
    int x, y;

    mostraFich("cp_ex1.dat"); // ALÍNEA A)

    mostraInicioFim("cp_ex1.dat");

    x = existe("cp_ex1.dat", "Braga"); // ALÍNEA B)
    printf("%d\n", x);

    return 0;
}

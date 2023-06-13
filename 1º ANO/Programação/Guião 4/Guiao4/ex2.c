#include <stdio.h>
#include <stdlib.h>

// EXERCICÍO 2

/*void mostraFich(char *nome){
    FILE *f;
    int p;

    f = fopen(nome, "rb");
    if(f == NULL){
        printf("erro no acesso ao fichiero\n");
        return;
    }

    while (fread(&p, sizeof(int), 1, f) == 1)
        printf("%d\n", p);

    fclose(f);
}*/

void calcula(char *nome, float *media, int *soma) {
    FILE *f;
    int p;

    *soma = 0;
    unsigned int conta = 0;

    f = fopen(nome, "rb");
    if (f == NULL) {
        printf("erro no acesso ao fichiero\n");
        return;
    }

    while (fread(&p, sizeof(int), 1, f) == 1) {
        *soma = *soma + p;
        conta++;
    }

    *media = (float)*soma / conta;

    printf("Soma = %d\n", *soma);
    printf("Media = %f\n", *media);

    fclose(f);
}

int* criaVetor(char *nomeFich, int *tam){
    FILE *f;
    int p;
    int *aux;

    f = fopen(nomeFich, "rb");
    if (f == NULL) {
        printf("erro no acesso ao fichiero\n");
        return NULL;
    }
    while (fread(&p, sizeof(int), 1, f) == 1){
        if(p % 2 == 0){
            (*tam)++;
        }
    }

    aux = malloc(sizeof(int) * (*tam));
    int i = 0;
    rewind(f);
    while (fread(&p, sizeof(int), 1, f) == 1){
        if(p % 2 == 0){
            aux[i] = p;
            i++;
        }
    }

    fclose(f);
    return aux;
}

/*
int main(){
    int soma = 0;
    float media = 0.0;
    int tam = 0;
    int *v = NULL;

    mostraFich("valoresEx2.bin");

    calcula("valoresEx2.bin", &media, &soma); // ALÍNEA A)

    v = criaVetor("valoresEx2.bin", &tam); // ALÍNEA B)
    for (int i = 0; i < tam; i++) {
        printf("%d\t", v[i]);
    }

    return 0;
}*/

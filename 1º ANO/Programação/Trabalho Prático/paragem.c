#include "paragem.h"

// ADICIONA UMA PARAGEM.

pg adicionaParagem(pg tab, int *n){
    pg aux;

    char nome[99];
    getchar();
    printf("Nome da paragem:");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *n; i++) {
        if(strcmp(tab[i].nome, nome) == 0){
            printf("Nome existente!\n");
            return tab;
        }
    }

    aux = realloc(tab, sizeof(pgm)*(*n+1));

    if(aux != NULL){
        tab = aux;
        strcpy(tab[*n].nome, nome);
        adicionaCodigoParagem(tab[*n].codigo_alfanumerico, sizeof(tab[*n].codigo_alfanumerico));
        (*n)++;
    }

    return tab;
}

// MOSTRA AS PARAGENS EXISTENTES.

void visualizaParagens(pg tab, int n){
    pg aux = tab;
    for (int i = 0; i < n; ++i) {
        printf("%s # %s\n", aux[i].nome, aux[i].codigo_alfanumerico);
    }
}

// VERIFICA SE UMA PARAGEM EXISTE.

pg paragemExiste(pg tab, int *n, char *nomeParagem){
    pg aux = tab;

    for (int i = 0; i < *n; i++) {
        if(strcmp(aux[i].nome, nomeParagem) == 0){
            printf("Paragem Encontrada!\n");
            //return aux;
            return &aux[i];
        }
    }

    printf("Paragem Inexistente!\n");
    return NULL;
}

// CRIA O CÓDIGO ALFANUMÉRICO.

void adicionaCodigoParagem(char *codigo, int tamanho){
    const char letnum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    unsigned int tam = strlen(letnum);

    srand(time(NULL));

    for (int i = 0; i < tamanho - 1; i++) {
        codigo[i] = letnum[rand() % tam];
    }

    codigo[tamanho - 1] = '\0';
}

// ADICIONAR PARAGENS A PARTIR DE UM FICHEIRO DE TEXTO.

pg adicionaParagensFicheiro(pg tab, int *n) {
    FILE *f;

    pg aux = tab;

    char nomeFicheiro[99];
    char nomeParagem[99];
    char codigoAlfa[5];

    getchar();

    printf("Introduz nome do ficheiro:");
    fgets(nomeFicheiro, sizeof(nomeFicheiro), stdin);
    nomeFicheiro[strcspn(nomeFicheiro, "\n")] = '\0';

    f = fopen(nomeFicheiro, "r");
    if (f == NULL) {
        printf("Erro no Acesso ao Ficheiro!\n");
        return NULL;
    }

    while (fscanf(f, "%[^#]# %s%*[\n ]", nomeParagem, codigoAlfa) != EOF) {
        for (int i = 0; i < *n; i++) {
            if (strcmp(tab[i].nome, nomeParagem) == 0) {
                printf("Nome existente!\n");
                return tab;
            }
        }

        // retira o espaço da string.
        int tamanho = strlen(nomeParagem);
        nomeParagem[tamanho - 1] = '\0';

        aux = realloc(tab, sizeof(pgm) * (*n + 1));

        if (aux != NULL) {
            tab = aux;
            strcpy(tab[*n].nome, nomeParagem);
            strcpy(tab[*n].codigo_alfanumerico, codigoAlfa);
            (*n)++;
        }
    }

    fclose(f);
    return tab;
}

// VISUALIZA PARAGENS DO FICHEIRO.

void visualizaParagensFicheiro(pg tab, int n){
    pg aux = tab;
    for (int i = 0; i < n; ++i) {
        printf("%s # %s", aux[i].nome, aux[i].codigo_alfanumerico);
    }
}
#include "linha.h"

// ELIMINAR UMA PARAGEM.

pg eliminaParagem(pg tab, int *n, ln linha){
    pg p;
    pgm aux;

    char codigo[99];

    printf("Codigo da paragem a eliminar:");
    scanf("%s", codigo);

    while (linha != NULL){
        tab = linha->lista;
        for (int i = 0; i < *n; i++) {
            if (strcmp(tab[i].codigo_alfanumerico, codigo) == 0) {
                printf("Paragem pertence a uma linha!\n");
                return tab;
            }
        }
        linha = linha->prox;
    }

    for(int i = 0; i < *n; i++){
        if(strcmp(codigo, tab[i].codigo_alfanumerico) == 0){
            aux = tab[i];
            tab[i] = tab[*n-1];
            p = realloc(tab, sizeof(pgm)*(*n-1));
            if(p != NULL){
                tab = p;
                (*n)--;
                return tab;
            }else{
                tab[i] = aux;
            }
        }
    }

    printf("Codigo Inexistente!\n");
    return tab;
}

// ADICIONA UMA LINHA.

ln adicionaLinha(ln tab, pg par, int *n){
    ln novaLinha;
    ln aux = tab;

    char nomeLinha[99];
    char nomeParagem[99];

    novaLinha = malloc(sizeof(lna));
    if(novaLinha == NULL){
        return tab;
    }

    getchar();

    printf("Nome da Linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strcspn(nomeLinha, "\n")] = '\0';

    while (aux != NULL){
        if(strcmp(aux->nome, nomeLinha) == 0){
            printf("Nome existente!\n");
            return tab;
        }
        aux = aux->prox;
    }

    strcpy(novaLinha->nome, nomeLinha);
    novaLinha->nParagens = 0;
    novaLinha->prox = NULL;
    novaLinha->lista = NULL;

    while (1){
        printf("Nome da Paragem:");
        fgets(nomeParagem, sizeof(nomeParagem), stdin);
        nomeParagem[strcspn(nomeParagem, "\n")] = '\0';

        if(strcmp(nomeParagem, "FIM") == 0){
            break;
        }

        pg paragemNova = paragemExiste(par, n, nomeParagem);
        printf("%s\n", paragemNova->nome);

        if(paragemNova == NULL){
            printf("Paragem inexistente!\n");
            break;
        } else{
            ++novaLinha->nParagens;
            novaLinha->lista = realloc(novaLinha->lista, novaLinha->nParagens * sizeof(pgm));
            novaLinha->lista[novaLinha->nParagens - 1] = *paragemNova;
        }
    }

    printf("%d\n", novaLinha->nParagens);
    printf("Todas as paragens adicionadas!\n");
    if(tab == NULL){
        tab = novaLinha;
    } else{
        ln linha = tab;
        while (linha->prox != NULL){
            linha = linha->prox;
        }
        linha->prox = novaLinha;
    }

    return tab;
}

// MOSTRA AS LINHAS E PARAGENS EXISTENTES.

void visualizaLinhas(ln tab){
    ln aux = tab;
    pg aux1;

    while (aux != NULL){
        aux1 = aux->lista;
        printf("%s\n", aux->nome);
        for (int i = 0; i < aux->nParagens; i++) {
            printf("%s # %s\n", aux1[i].nome, aux1[i].codigo_alfanumerico);
        }
        aux = aux->prox;
    }
}

// ATUALIZAR LINHA.

ln atualizaLinha(ln tab, pg par, int *n){
    ln aux = tab;
    pgm aux1;

    char nomeLinha[99];
    char nomeParagem[99];
    int opc;

    getchar();

    printf("Nome da Linha:");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strcspn(nomeLinha, "\n")] = '\0';

    while (aux != NULL){
        if(strcmp(aux->nome, nomeLinha) == 0){
            break;
        }
        aux = aux->prox;
    }

    printf("Linha que vai ser atualizada: %s\n", aux->nome);

    printf("Adicionar (1) ou Eliminar (2) paragens:");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            printf("Nome da Paragem:");
            getchar();
            fgets(nomeParagem, sizeof(nomeParagem), stdin);
            nomeParagem[strcspn(nomeParagem, "\n")] = '\0';

            if(strcmp(nomeParagem, "FIM") == 0){
                break;
            }

            pg paragemNova = paragemExiste(par, n, nomeParagem);

            if(paragemNova == NULL){
                printf("Paragem Inexistente!\n");
            } else{
                ++aux->nParagens;
                aux->lista = realloc(aux->lista, aux->nParagens * sizeof(pgm));
                aux->lista[aux->nParagens - 1] = *paragemNova;
            }
            break;
        case 2:
            printf("Nome da Paragem:");
            getchar();
            fgets(nomeParagem, sizeof(nomeParagem), stdin);
            nomeParagem[strcspn(nomeParagem, "\n")] = '\0';

            if(strcmp(nomeParagem, "FIM") == 0){
                break;
            }

            pg paragemEliminar = paragemExiste(par, n, nomeParagem);
            pg p;

            if(paragemEliminar == NULL){
                printf("Paragem Inexistente!\n");
            } else{
                while (aux != NULL){
                    for (int i = 0; i < aux->nParagens; i++) {
                        if(strcmp(aux->lista[i].nome, nomeParagem) == 0){
                            aux1 = aux->lista[i];
                            aux->lista[i] = aux->lista[aux->nParagens-1];
                            p = realloc(aux->lista, (aux->nParagens-1) * sizeof(pgm));
                            if(p != NULL){
                                aux->lista = p;
                                aux->nParagens--;
                                return tab;
                            } else{
                                aux->lista[i] = aux1;
                            }
                        }
                    }
                    aux = aux->prox;
                }
            }
            break;
    }
    return tab;
}

// ADICIONAR LINHA E PARAGENS EXISTENTES A PARTIR DE UM FICHEIRO DE TEXTO.

ln adicionaLinhaFicheiro(ln tab, pg par, int *n){
    FILE *f;

    ln aux = tab;
    ln novaLinha;

    char nomeFicheiro[99];
    char nomeLinha[99];
    char nomeParagem[99];
    char codigoAlfa[5];

    novaLinha = malloc(sizeof(lna));
    if(novaLinha == NULL){
        return tab;
    }

    getchar();

    printf("\nIntroduz nome do ficheiro:");
    fgets(nomeFicheiro, sizeof(nomeFicheiro), stdin);
    nomeFicheiro[strcspn(nomeFicheiro, "\n")] = '\0';

    f = fopen(nomeFicheiro, "rb");
    if(f == NULL){
        printf("Erro no Acesso ao Ficheiro!\n");
        return NULL;
    }

    fscanf(f, "%[^\n]", nomeLinha);

    while (aux != NULL){
        if(strcmp(aux->nome, nomeLinha) == 0){
            printf("Nome existente!\n");
            return tab;
        }
        aux = aux->prox;
    }

    strcpy(novaLinha->nome, nomeLinha);
    novaLinha->nParagens = 0;
    novaLinha->prox = NULL;
    novaLinha->lista = NULL;

    // VER MELHOR ESTE CICLO. !!!

    while (fscanf(f, " %[^#]# %s%*[\n ]", nomeParagem, codigoAlfa) != EOF) {
        // retira o espaço da string.
        int tamanho = strlen(nomeParagem);
        nomeParagem[tamanho - 1] = '\0';

        // Erro está aqui.
        pg paragemNova = paragemExiste(par, n, nomeParagem);
        // Devolve NULL, mesmo quando são iguais.

        if(paragemNova == NULL){
            printf("Paragem inexistente!\n");
        } else{
            ++novaLinha->nParagens;
            novaLinha->lista = realloc(novaLinha->lista, novaLinha->nParagens * sizeof(pgm));
            novaLinha->lista[novaLinha->nParagens - 1] = *paragemNova;
        }
    }

    if(tab == NULL){
        tab = novaLinha;
    } else{
        ln linha = tab;
        while (linha->prox != NULL){
            linha = linha->prox;
        }
        linha->prox = novaLinha;
    }

    fclose(f);
    return tab;
}

// ARMAZENAMENTO BINÁRIO.

void armazenaBinario(ln tab, pg par, int *n){
    FILE *f;

    ln aux = tab;

    f = fopen("dados.dat", "wb");
    if(f == NULL){
        printf("Erro no acesso ao ficheiro!\n");
        return;
    }

    while (aux != NULL){
        pg auxP = aux->lista;
        fwrite(aux->nome, sizeof(lna), 1, f);
        for (int i = 0; i < aux->nParagens; i++) {
            //fwrite(strcat(auxP[i].nome, strcat(" # ", auxP[i].codigo_alfanumerico)), sizeof(pgm), 1, f);
            fwrite(auxP[i].nome, sizeof(auxP[i].nome), 1, f);
            fwrite(" # ", sizeof(char), 1, f);
            fwrite(auxP[i].codigo_alfanumerico, sizeof(auxP[i].codigo_alfanumerico), 1, f);
        }
        aux = aux->prox;
    }

    fclose(f);
}

// CALCULAR PERCURSO (UMA ÚNICA LINHA).

void calculaPercurso(ln tab, pg par, int *n){
    ln aux = tab;

    char nomeOrigem[99];
    char nomeDestino[99];

    getchar();

    printf("Origem:");
    fgets(nomeOrigem, sizeof(nomeOrigem), stdin);
    nomeOrigem[strcspn(nomeOrigem, "\n")] = '\0';

    printf("Destino:");
    fgets(nomeDestino, sizeof(nomeDestino), stdin);
    nomeDestino[strcspn(nomeDestino, "\n")] = '\0';

    while (aux != NULL){
        pg origem = aux->lista;
        pg destino = aux->lista;
        int iOrigem = 0;
        int iDestino = 0;

        for (int i = 0; i < aux->nParagens; i++) {
            if(strcmp(origem[i].nome, nomeOrigem) == 0){
                iOrigem = i;
            }
            if(strcmp(destino[i].nome, nomeDestino) == 0){
                iDestino = i;
            }
        }

        if(iOrigem < iDestino){
            for(int i = iOrigem; i <= iDestino; i++){
                if(i != iDestino)
                    printf("%s -> ", aux->lista[i].nome);
                else
                    printf("%s\n", aux->lista[i].nome);
            }
        } else{
            for (int i = iOrigem; i >= iDestino; i--) {
                if(i != iDestino)
                    printf("%s -> ", aux->lista[i].nome);
                else
                    printf("%s\n", aux->lista[i].nome);
            }
        }
        aux = aux->prox;
    }
}

// MOSTRAS AS LINHAS QUE PASSAM NUMA DETERMINADA PARAGEM.

void visualizaLinhasParagem(ln tab){
    ln aux = tab;
    pg auxP;

    char nomeParagem[99];

    getchar();

    printf("Nome da paragem:");
    fgets(nomeParagem, sizeof(nomeParagem), stdin);
    nomeParagem[strcspn(nomeParagem, "\n")] = '\0';

    while (aux != NULL){
        auxP = aux->lista;
        for (int i = 0; i < aux->nParagens; i++) {
            if(strcmp(auxP[i].nome, nomeParagem) == 0)
                printf("%s\n", aux->nome);
        }
        aux = aux->prox;
    }
}

// DÁ LOAD DO FICHEIRO BINÁRIO.

ln carregaBinario(ln tab, pg par, int *n) {
    FILE *f;

    f = fopen("dados.dat", "rb");
    if (f == NULL) {
        printf("Erro no acesso ao ficheiro!\n");
        return NULL;
    }

    while (!feof(f)) {
        ln novaLinha = malloc(sizeof(lna));
        if (novaLinha == NULL) {
            printf("Erro na alocação de memória!\n");
            fclose(f);
            return NULL;
        }

        if (fread(novaLinha->nome, sizeof(lna), 1, f) != 1) {
            free(novaLinha);
            break;
        }

        novaLinha->lista = NULL;

        // FALTAM AS PARAGENS.

        if (tab == NULL) {
            tab = novaLinha;
        } else {
            ln aux = tab;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novaLinha;
        }
    }

    fclose(f);
    return tab;
}
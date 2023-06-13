#include <stdio.h>

// EXERCICÍO 4 (GUIÃO 4)

void mostraTxt(char *nome){
    FILE *f;
    int c;

    f = fopen(nome,"rt");
    if(f == NULL)
        return;

    while ((c = fgetc(f)) != EOF)
        putchar(c);
    fclose(f);
}

// EXERCICÍO 6 (GUIÃO 4)

void numeraTxt(char *nome){
    FILE *f, *fp;
    char c[999];
    int conta = 0;

    f = fopen(nome,"rt");
    if(f == NULL)
        return;

    fp = fopen("abc1.txt","wt");
    if(fp == NULL)
        return;

    while (fgets(c,sizeof(c),f) != NULL)
        fprintf(fp,"%d: %s", ++conta, c);
    fclose(fp);
    fclose(f);
}

// EXERCICÍO 7 (GUIÃO 4)

void mostraLinhaTxt(char *nome, int linha){
    FILE *f;
    char c[999];
    int conta = 0;

    f = fopen(nome,"rt");
    if(f == NULL)
        return;

    while (fgets(c,sizeof(c),f) != NULL){
        ++conta;
        if(conta == linha){
            printf("%s", c);
        }
    }

    fclose(f);
}

// EXERCICÍO 8 (GUIÃO 4)

void vogalMaisComumTxt(char *nome){
    FILE *f;
    int c;
    int contaA = 0, contaE = 0, contaI = 0, contaO = 0, contaU = 0;

    f = fopen(nome,"rt");
    if(f == NULL)
        return;

    while ((c = fgetc(f)) != EOF){
        if(c == 'a' || c == 'A')
            contaA++;
        else if(c == 'e' || c == 'E')
            contaE++;
        else if(c == 'i' || c == 'I')
            contaI++;
        else if(c == 'o' || c == 'O')
            contaO++;
        else if(c == 'u' || c == 'U')
            contaU++;
    }

    if(contaA > contaE && contaA > contaI && contaA > contaO && contaA > contaU)
        printf("Vogal mais comum: A");
    else if(contaE > contaA && contaE > contaI && contaE > contaO && contaE > contaU)
        printf("Vogal mais comum: E");
    else if(contaI > contaA && contaI > contaE && contaI > contaO && contaI > contaU)
        printf("Vogal mais comum: I");
    else if(contaO > contaA && contaO > contaE && contaO > contaI && contaO > contaU)
        printf("Vogal mais comum: O");
    else if(contaU > contaA && contaU > contaI && contaU > contaO && contaU > contaE)
        printf("Vogal mais comum: U");

    fclose(f);
}

// EXERCICÍO 9 (GUIÃO 4)

void calculaNotas(char *nome){
    FILE *f;
    int totAl = 0, totProvas = 0;
    char palavra1[10], palavra2[10], palavra3[10];
    int peso[5];
    int nota[5];
    double soma = 0.0;
    float media;

    f = fopen(nome, "r");
    if(f == NULL){
        printf("erro no acesso ao ficheiro\n");
        return;
    }

    // Leitura das duas primeiras linhas
    fscanf(f, "%s %s %s : %d", palavra1, palavra2, palavra3, &totAl);
    fscanf(f, "%*[^:] : %d", &totProvas);

    printf("Alunos: %d\nProvas: %d\n", totAl, totProvas);

    // Leitura da terceira linha
    fscanf(f, "%*[^:] : %d %d %d %d %d", &peso[0], &peso[1], &peso[2], &peso[3], &peso[4]);
    fscanf(f, " Aluno 1: %d %d %d %d %d", &nota[0], &nota[1], &nota[2], &nota[3], &nota[4]);

    // fscanf(f, "%*[^:] :");

    for (int i = 0; i < 5; i++) {
        soma += nota[i] * (peso[i]/100.0);
    }

    printf("Media Aluno 1: %f", soma);

    fclose(f);
}

int main() {

    //mostraTxt("abc.txt");

    //numeraTxt("abc.txt");
    //putchar('\n');

    //mostraTxt("abc1.txt");
    //putchar('\n');

    //mostraLinhaTxt("abc1.txt", 3);
    //putchar('\n');

    //vogalMaisComumTxt("abc.txt");
    //putchar('\n');

    calculaNotas("notas_ex9.txt");

    return 0;
}

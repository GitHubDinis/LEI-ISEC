#include <stdio.h>
#include <string.h>

#include "cliente.h"

typedef struct cliente cliente;
struct cliente{
    char nome[200];
    char morada[200];
    int conta;
    int montante;
};

void printFile(char *nameFile){
    FILE *fp;
    cliente c;

    fp = fopen(nameFile,"rb");
    if (fp == NULL)
        printf("Erro ao abrir ficheiro\n");

    while(fread(&c,sizeof(cliente),1,fp) == 1){
        printf("Nome: %s\tMorada: %s\tConta: %d\tMontante: %d\n",c.nome,c.morada,c.conta,c.montante);
    }
    fclose(fp);
}

void printInfoFile(char *nameFile){
    FILE *fp;
    cliente c;

    fp = fopen(nameFile, "rb");
    if (fp == NULL)
        printf("Erro ao abrir ficheiro\n");

    fseek(fp,0,SEEK_END);
    printf("Numero de bytes: %ld\n", ftell(fp));
    printf("Numero de clientes: %d\n", ftell(fp)/sizeof(cliente));

    fclose(fp);
}

void printFileInv(char *nameFile){
    FILE *fp;
    cliente c;

    fp = fopen(nameFile, "rb");
    if (fp == NULL)
        printf("Erro ao abrir ficheiro\n");

    fseek(fp, 0, SEEK_END);
    int nClientes = ftell(fp)/sizeof(cliente);

    for (int j = 1; j < nClientes+1; j++) {
        fseek(fp, -(sizeof(cliente)*j), SEEK_END);
        fread(&c, sizeof(cliente),1,fp);
        printf("Nome do Cliente: %s\n", c.nome);
    }

    fclose(fp);
}

void trasnfere(char *nomeF, char *or, char *dest, int valor){
    FILE *f;
    cliente c;

    f = fopen(nomeF, "rb+");
    if (f == NULL)
        printf("Erro ao abrir ficheiro\n");

    while (fread(&c, sizeof(cliente), 1, f) == 1){
        if(strcmp(c.nome, or) == 0){
            c.montante = c.montante - valor;
            fseek(f, -sizeof(cliente), SEEK_CUR);
            fwrite(&c, sizeof(cliente), 1,f);
            break;
        }
    }

    rewind(f); // fseek para o início

    while (fread(&c, sizeof(cliente), 1, f) == 1){
        if(strcmp(c.nome, dest) == 0){
            c.montante = c.montante + valor;
            fseek(f, -sizeof(cliente), SEEK_CUR);
            fwrite(&c, sizeof(cliente), 1, f);
            break;
        }
    }

    fclose(f);
}

int trasnfere1(char *nomeF, char *or, char *dest, int valor){
    FILE *f;
    cliente c;

    int existe = 0;

    f = fopen(nomeF, "rb+");
    if (f == NULL)
        printf("Erro ao abrir ficheiro\n");

    while (fread(&c, sizeof(cliente), 1, f) == 1){
        if(strcmp(c.nome, or) == 0){
            printf("Cliente origem encontrado!\n");
            existe = 1;
            break;
        }
    }

    rewind(f);

    if(existe == 0) {
        printf("Cliente origem inexistente!\n");
        return 0;
    }else {
        existe = 0;
        while (fread(&c, sizeof(cliente), 1, f) == 1){
            if(strcmp(c.nome, or) == 0){
                printf("Cliente destino encontrado!\n");
                existe = 1;
                break;
            }
        }
    }

    if (existe == 0) {
        printf("Cliente destino inexistente!\n");
        return 0;
    }else{
        while (fread(&c, sizeof(cliente), 1, f) == 1){
            if(strcmp(c.nome, or) == 0){
                c.montante = c.montante - valor;
                fseek(f, -sizeof(cliente), SEEK_CUR);
                fwrite(&c, sizeof(cliente), 1,f);
                break;
            }
        }

        rewind(f); // fseek para o início

        while (fread(&c, sizeof(cliente), 1, f) == 1){
            if(strcmp(c.nome, dest) == 0){
                c.montante = c.montante + valor;
                fseek(f, -sizeof(cliente), SEEK_CUR);
                fwrite(&c, sizeof(cliente), 1, f);
                break;
            }
        }
    }

    fclose(f);
}

void adiciona(char *nome, struct cliente novo){
    cliente c;
    FILE *f, *g;

    int flag = 0;

    f = fopen(nome, "rb");
    if(f == NULL) return;

    g = fopen("t.dat", "wb");
    if(g == NULL) { fclose(f);return;}

    while (fread(&c, sizeof(cliente), 1, f) == 1){
        if (strcmp(c.nome, novo.nome) > 0 && flag == 0){
            fwrite(&novo, sizeof(novo), 1, g);
            flag = 1;
        }
        fwrite(&c, sizeof(cliente), 1, g);
    }
    if(flag == 0){
        fwrite(&novo, sizeof(novo), 1, g);
    }

    fclose(f);
    fclose(g);

    remove(nome);
    rename("t.dat", nome);
}

int main() {

    //printFile("Ex10_clientes1.dat"); // A)

    //printInfoFile("Ex10_clientes1.dat"); // B)

    //printFileInv("Ex10_clientes1.dat"); // F)

    //trasnfere("Ex10_clientes1.dat", "Ana Silva", "Dinis Pais", 100);  // E

    //printFile("Ex10_clientes1.dat");

    //trasnfere1("Ex10_clientes1.dat", "Ana Silva", "Dinis Pais", 100); // ALÍNEA ADICIONAL

    printFile("Ex10_clientes1.dat");

    adiciona("Ex10_clientes1.dat", (struct cliente){"Zilda","Coimbra",1234, 1000}); // D

    putchar('\n');

    printFile("Ex10_clientes1.dat");

    return 0;
}

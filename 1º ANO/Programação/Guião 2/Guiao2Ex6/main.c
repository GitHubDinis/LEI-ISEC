#include <stdio.h>
#include <stdlib.h>

// GUIÃO 2 (EXERCICÍO 6)

#include "agenda.h"

int main() {

    // ALÍNEA B)

    pct tab = NULL;
    int i, total = 0;
    char nome[99], nome1[99];

    for (int j = 0; j < 3; j++) {
        tab = addC(tab, &total);
    }
    listaC(tab, total);

    //printf("Nome: ");
    //scanf("%s", nome);

    //mostraNum(tab, nome, total);

    //atualizaNum(tab, nome, total);

    printf("Nome a eliminar: ");
    scanf("%s", nome1);

    eliminaC(tab, nome1, &total);

    listaC(tab, total);

    free(tab);

    return 0;
}

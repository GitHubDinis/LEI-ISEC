#include <stdio.h>
#include <stdlib.h>

////////////// exame época normal 09/02/2021 /////////////////

//////////////   Pergunta 3  //////////////////////////////////

//nome: Dinis Meireles de Sousa Falcão

//número: 2020130403

// Estratégia de resolução:

// Dados de Entrada: int i (para o ciclo); int alteraLetra (para contagem da Letra que se vai alterar);

// Conhecimento Requerido: Sting fa não deve ter mais do que 10 palavras;

// Resultados Pretendidos: Mudança da última letra de cada palavra numa frase com menos de 11 palavras;

// Estratégia:
// Inicializar alteraLetra a 0;
// Fazer um ciclo que corra todas as letras e, quando estiver em cima da última letra de cada palavra, substituir pelo número de ordem da mesma palavra;
// A última letra será antes de cada espaço, logo se fa[i]==' ', fa[i-1] é a última letra;
// strlen(fa) para ver o cumprimento da string;
// Quando não houverem mais palavras, devolve '!'.


char ultimaLetra(char fa[]){

    int i;
    int alteraLetra = 0;

    for(i = 0; strlen(fa); i++){

        if (i == 0)
            continue;

        if (fa[i] == ' ')
            fa[i - 1] = alteraLetra;
            alteraLetra++;

    }
    return '!';
}


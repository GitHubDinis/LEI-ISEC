#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int mat[][2], int *v)
{

	int     i;
	float   sum_weight, sum_profit;
	int total=0;
	int j, flag;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
			for(j=i+1; j<d.numGenes;j++){

				if(sol[j]==1 && *(d.mat+i*d.numGenes+j)==1){
					total++;
				}

			}
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}

	if (sum_weight > d.capacity) {
		*v = 0;
		return 0;
	}else{


        // Solucao v�lida
		*v = 1;
		return total;
		}
}

 float quality(int sol[], struct info d, int mat[][2], int *v){
	int     i;
	float   sum_weight, sum_profit;
	int total=0;
	int j, flag;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}

        // Solucao v�lida
		return sum_profit;

 }

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, struct info d, int mat[][2], int *grafo)
{
	int i;

	for (i=0; i<d.popsize; i++){
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
		pop[i].quality = quality(pop[i].p, d, mat, &pop[i].valido);
	}
}

void gera_vizinho(int sol[], int v[], int mat[][2], struct info d)
{
    int i, min, max, p1, p2, p3 , p4;

    // Clonar a solucao 
    for (i=0; i < d.numGenes; i++){
        v[i] = sol[i];
	}
        do
            p1=random_l_h(0, d.numGenes-1);
        while(v[p1] != 0);
	// Encontra posicao com valor 0
        do
            p2=random_l_h(0, d.numGenes-1);
        while(v[p2] != 1);

        v[p1] = 0;
        v[p2] = 1;

}

void trepa_colinas(pchrom pop, struct info d, int mat[][2])
{

    int     i, j;
    chrom   vizinho;

    for (i=0; i<d.popsize; i++)
    {
        for (j=0; j<d.numGenerations; j++)
        {
            gera_vizinho(pop[i].p, vizinho.p, mat, d);
            vizinho.fitness = eval_individual(vizinho.p, d, mat, &vizinho.valido);
            if (vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
        }
    }
}
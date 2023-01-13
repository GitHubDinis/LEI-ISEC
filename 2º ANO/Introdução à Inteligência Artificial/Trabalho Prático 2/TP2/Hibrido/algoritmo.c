#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"
#include <stdbool.h>

// Preenche uma estrutura com os progenitores da pr�xima gera��o, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Par�metros de entrada: popula��o actual (pop), estrutura com par�metros (d) e popula��o de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, j, k, *pos;
	int out, best;
// alocacoa de espaco para um vetor de inteiros tsize
	pos = malloc(d.tsize*sizeof(int));

	for(i=0; i<d.popsize;i++)
	{
		for(j=0; j<d.tsize; j++)
        {
            do
            {// escolhe uma pos random entre 0 e popsize-1
                pos[j] = random_l_h(0, d.popsize-1);
                // Verifica se existem pos iguais
                out = 0;
                for (k=0; k<j; k++)
                {
                    if (pos[k]==pos[j])
                        out = 1;
                }
            }while (out);

            // Guardar a melhor pos
            if (j==0 || pop[pos[j]].fitness > pop[pos[best]].fitness)		// Problema de maximizacao
                best = j;
        }
        parents[i] = pop[pos[best]];
	}
	free(pos);
}

// Operadores geneticos a usar na gera��o dos filhos
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
    // Recombina��o com um ponto de corte
	crossover(parents, d, offspring);
	// Muta��o bin�ria
	mutation(offspring, d);
}

// Preenche o vector descendentes com o resultado das opera��es de recombina��o
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point, point2;

	for (i=0; i<d.popsize; i+=2)
	{
		if (rand_01() < d.pr)
		{
			point = random_l_h(0, d.numGenes-1);
			point2 = random_l_h(point+1, d.numGenes-1);
			for (j=0; j<point; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i+1].p[j] = parents[i+1].p[j];
			}
			for (j=0; j<point2; j++)
			{
				offspring[i].p[j] = parents[i+1].p[j];
				offspring[i+1].p[j] = parents[i].p[j];
			}
			for (j=point; j<d.numGenes; j++)
			{
				offspring[i].p[j]= parents[i+1].p[j];
				offspring[i+1].p[j] = parents[i].p[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}

// Muta��o bin�ria com v�rios pontos de muta��o
// Par�metros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d) 
void mutation(pchrom offspring, struct info d) {
	int i, j;
	int index_1, index_2;

	for (i = 0; i < d.popsize; i++) {
		if (rand_01() < d.pm * d.numGenes) { // pm é a probabilidade de mutação de cada gene, mas aqui calculamos a probabilidade de mutação do individuo
			// Retira um item aleatoriamente
			do
				index_1 = random_l_h(0, d.numGenes - 1);
			while (offspring[i].p[index_1] == 1);
			
			// Insere um item aleatoriamente
			do
				index_2 = random_l_h(0, d.numGenes - 1);
			while (offspring[i].p[index_2] == 0);

			offspring[i].p[index_1] = !offspring[i].p[index_1];
			offspring[i].p[index_2] = !offspring[i].p[index_2];
		}
	}
}
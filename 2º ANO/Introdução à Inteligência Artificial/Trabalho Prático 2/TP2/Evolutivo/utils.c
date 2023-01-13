#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Inicializa��o do gerador de n�meros aleat�rios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Leitura dos par�metros e dos dados do problema
// Par�metros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Par�metros de sa�da: Devolve a estrutura com os par�metros
struct info init_data(char *filename, int mat[][2],  int popsize, float pm, float pr, int tsize, int numGenerations, int *grafo)
{

	FILE *f;
	int *p, *q;
	int i, j, arestas, k, l, c, total;
	char buffer[20];
	struct  info x;


	f=fopen(filename, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	// Numero de iteracoes
	fscanf(f, "%s %d", buffer, &x.capacity);

	// Numero de vertices
	fscanf(f, "%s %s %d %d",buffer, buffer, &x.numGenes, &arestas);
	// Alocacao dinamica da matriz
	x.popsize = popsize;
	x.pm = pm;
	x.pr = pr;
	x.tsize = tsize;
	x.numGenerations = numGenerations;

	p = malloc(sizeof(int)*(x.numGenes)*(x.numGenes));
	x.mat = malloc(sizeof(int)*(x.numGenes)*(x.numGenes));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}

	for(i=0; i<(x.numGenes)*(x.numGenes); i++){
		p[i]=0;
	}
	
	// Preenchimento da matriz
	for(i=0; i<arestas; i++){
		
		fscanf(f, "%s %d %d", buffer, &l, &c );
		l--;
		c--;
		p[l * (x.numGenes) + c] = 1;
		p[c * (x.numGenes) + l] = 1;


	}

	memcpy(x.mat, p, sizeof(int)*(x.numGenes)*(x.numGenes));



    for(int i=0; i<x.numGenes; i++){

		total = 0;

    	for(int j=0; j<x.numGenes; j++){
		
	    	total += p[i*x.numGenes+j];
		}	

		mat[i][0] = 1;
		mat[i][1] = total;

	}

	printf("Matriz: \n");
	escreve_matriz(p,x.numGenes);


	if (x.numGenes > MAX_OBJ)
	{
		printf("Number of itens is superior to MAX_OBJ\n");
		exit(1);
	}
	x.ro = 0.0;
	
	fclose(f);
	// Devolve a estrutura com os par�metros
	return x;
}

// Simula o lan�amento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche da estrutura da popula��o apenas o vector bin�rio com os elementos que est�o dentro ou fora da mochila
pchrom init_pop(struct info d)
{
	int     i, j, x, sum=0;
	pchrom  indiv;

	indiv = malloc(sizeof(chrom)*d.popsize);
	if (indiv==NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}

	for (i=0; i<d.popsize; i++)
	{
		for (j=0; j<d.numGenes; j++)
			
			indiv[i].p[j] = 0;

	}

	for (i=0; i<d.popsize; i++)
	{
		for (j=0; j<d.capacity; j++){

		do
			x = random_l_h(0, d.numGenes-1);
        while(indiv[i].p[x] != 0);
        indiv[i].p[x]=1;
		}
	}
	return indiv;
}

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d) e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual
chrom get_best(pchrom pop, struct info d, chrom best)
{
	int i;

	for (i=0; i<d.popsize; i++)
	{
		if (best.fitness < pop[i].fitness)
			best=pop[i];
	}
	return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)
void write_best(chrom x, struct info d)
{
	int i;

	printf("\nBest individual: %4.1f\n", x.fitness);
	for (i=0; i<d.numGenes; i++)
		printf("%d", x.p[i]);
	putchar('\n');
}

void write_best_profit(pchrom x, struct info d)
{
	int i; 
	float best=0;

	for(i=0; i<d.popsize; i++){
		if (x[i].quality > best) {
			best = x[i].quality;
		}
	}
	printf("\nBest profit: %4.1f\n", best);
	putchar('\n');
}
void escreve_matriz (int *matriz, int n){

	for(int i=0; i<n; i++){

		for(int j=0; j<n; j++){
		
			printf("%d", matriz[i*n+j]);
		}
		printf("\n");
	}
}

bool digit_check(char key[]){  
	for(int i=0; i<strlen(key); i++){
		if(!isdigit(key[i])){
			return false;
		}
	}
	return true;
}

bool float_check(char key[]){
	int flag=0;

	for(int i=0; i<strlen(key); i++){
		if(key[i] == '.'){
			flag++;
		}
		if(!isdigit(key[i]) && key[i] != '.'){
			return false;
		}
	}
	if(flag == 1){
		return true;
	}

}



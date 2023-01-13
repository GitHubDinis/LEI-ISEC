#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *n, int *kV)
{
	FILE *f;
	int *p, *q;
	int i, j, arestas, k, l, c;
	char buffer[20];

	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	// Numero de iteracoes
	fscanf(f, "%s %d", buffer, kV);

	// Numero de vertices
	fscanf(f, "%s %s %d %d",buffer, buffer, n, &arestas);
	// Alocacao dinamica da matriz

	p = malloc(sizeof(int)*(*n)*(*n));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}

	for(i=0; i<(*n)*(*n); i++){
		p[i]=0;
	}
	
	// Preenchimento da matriz
	for(i=0; i<arestas; i++){
		
		fscanf(f, "%s %d %d", buffer, &l, &c );
		l--;
		c--;
		p[l * (*n) + c] = 1;
		p[c * (*n) + l] = 1;


	}

	printf("Matriz: \n");
	escreve_matriz(p,*n);

            
	fclose(f);
	return p;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v, int kV)
{
	int i, x;

	for(i=0; i<v; i++)
        sol[i]=0;
	for(i=0; i<kV; i++)
    {
        do
			x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nSolucao: ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i);
	printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
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
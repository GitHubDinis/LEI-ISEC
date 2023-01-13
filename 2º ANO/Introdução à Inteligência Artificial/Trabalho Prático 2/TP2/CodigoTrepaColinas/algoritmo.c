#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <stdbool.h>

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2, p3, p4, p5, p6, p7, p8 , p9 , p10, p11 , p12, var;

    if (var == 1){

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p1=random_l_h(0, n-1);
        while(b[p1] != 0);
	// Encontra posicao com valor 0
        do
            p2=random_l_h(0, n-1);
        while(b[p2] != 1);
	// Troca
        b[p1] = 1;
        b[p2] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p3=random_l_h(0, n-1);
        while(b[p3] != 0 || p3 == p1);
	// Encontra posicao com valor 0
        do
            p4=random_l_h(0, n-1);
        while(b[p4] != 1 || p4 == p2);
	// Troca
        b[p3] = 1;
        b[p4] = 0;

    }else if (var == 2) {

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p1=random_l_h(0, n-1);
        while(b[p1] != 0);
	// Encontra posicao com valor 0
        do
            p2=random_l_h(0, n-1);
        while(b[p2] != 1);
	// Troca
        b[p1] = 1;
        b[p2] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p3=random_l_h(0, n-1);
        while(b[p3] != 0 || p3 == p1);
	// Encontra posicao com valor 0
        do
            p4=random_l_h(0, n-1);
        while(b[p4] != 1 || p4 == p2);
	// Troca
        b[p3] = 1;
        b[p4] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p5=random_l_h(0, n-1);
        while(b[p5] != 0 || p5 == p1 || p5 == p3);
	// Encontra posicao com valor 0
        do
            p6=random_l_h(0, n-1);
        while(b[p6] != 1 || p6 == p2 || p6 == p4);
	// Troca
        b[p5] = 1;
        b[p6] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p7=random_l_h(0, n-1);
        while(b[p7] != 0 || p7 == p1 || p7 == p3 || p7 == p5);
	// Encontra posicao com valor 0
        do
            p8=random_l_h(0, n-1);
        while(b[p8] != 1 || p8 == p2 || p8 == p4 || p8 == p6);
	// Troca
        b[p7] = 1;
        b[p8] = 0;
    }else {

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p1=random_l_h(0, n-1);
        while(b[p1] != 0);
	// Encontra posicao com valor 0
        do
            p2=random_l_h(0, n-1);
        while(b[p2] != 1);
	// Troca
        b[p1] = 1;
        b[p2] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p3=random_l_h(0, n-1);
        while(b[p3] != 0 || p3 == p1);
	// Encontra posicao com valor 0
        do
            p4=random_l_h(0, n-1);
        while(b[p4] != 1 || p4 == p2);
	// Troca
        b[p3] = 1;
        b[p4] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p5=random_l_h(0, n-1);
        while(b[p5] != 0 || p5 == p1 || p5 == p3);
	// Encontra posicao com valor 0
        do
            p6=random_l_h(0, n-1);
        while(b[p6] != 1 || p6 == p2 || p6 == p4);
	// Troca
        b[p5] = 1;
        b[p6] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p7=random_l_h(0, n-1);
        while(b[p7] != 0 || p7 == p1 || p7 == p3 || p7 == p5);
	// Encontra posicao com valor 0
        do
            p8=random_l_h(0, n-1);
        while(b[p8] != 1 || p8 == p2 || p8 == p4 || p8 == p6);
	// Troca
        b[p7] = 1;
        b[p8] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p9=random_l_h(0, n-1);
        while(b[p9] != 0 || p9 == p1 || p9 == p3 || p9 == p5 || p9 == p7);
	// Encontra posicao com valor 0
        do
            p10=random_l_h(0, n-1);
        while(b[p10] != 1 || p10 == p2 || p10 == p4 || p10 == p6 || p10 == p8);
	// Troca
        b[p9] = 1;
        b[p10] = 0;

        for(i=0; i<n; i++)
            b[i]=a[i];
	// Encontra posicao com valor 0
        do
            p11=random_l_h(0, n-1);
        while(b[p11] != 0 || p11 == p1 || p11 == p3 || p11 == p5 || p11 == p7 || p11 == p9);
	// Encontra posicao com valor 0
        do
            p12=random_l_h(0, n-1);
        while(b[p12] != 1 || p12 == p2 || p12 == p4 || p12 == p6 || p12 == p8 || p12 == p10);
	// Troca
        b[p11] = 1;
        b[p12] = 0;
    }

}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
	// Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
		// Gera vizinho
		gera_vizinho(sol, nova_sol, vert);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, vert);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz > custo)
        {
			substitui(sol, nova_sol, vert);
			custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}

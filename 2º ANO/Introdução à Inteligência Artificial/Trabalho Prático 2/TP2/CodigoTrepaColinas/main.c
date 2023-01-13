#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10
#define DEFAULT_IT 10
#define DEFAULT_VZ 1

int main(int argc, char *argv[])
{
    char    nome_fich[100], buffer[100];
    int     vert, k, runs, custo, best_custo, kV, num_it, var;
    int     *grafo, *sol, *best;
	float   mbf = 0.0;

    printf("MAXIMUM EDGE SUBRGRAPH PROBLEM!\n");

	do{

		printf("Nome do Ficheiro: ");
        gets(nome_fich);

		if(strcmp(nome_fich,"file1.txt") != 0 && strcmp(nome_fich,"file2.txt") != 0 && strcmp(nome_fich,"file3.txt") != 0 && strcmp(nome_fich,"file4.txt") != 0 && strcmp(nome_fich,"file5.txt") != 0 && strcmp(nome_fich, "teste.txt") != 0){
			printf("\nNome do ficheiro introduzido invalido\n");
		}

	}while(strcmp(nome_fich,"file1.txt") != 0 && strcmp(nome_fich,"file2.txt") != 0 && strcmp(nome_fich,"file3.txt") != 0 && strcmp(nome_fich,"file4.txt") != 0 && strcmp(nome_fich,"file5.txt") != 0 && strcmp(nome_fich, "teste.txt") != 0);


	do{	
		printf("\nNumero de runs: ");
		scanf("%s", buffer
        );
		if(!digit_check(buffer)){
			printf("\nPor favor introduza um numero inteiro\n");
		}
		if(digit_check(buffer) == true){
			runs = atoi(buffer);
		}

	}while(!digit_check(buffer));

	do{	
		printf("\nNumero de iteracoes: ");
		scanf("%s", buffer);
		if(!digit_check(buffer)){
			printf("\nPor favor introduza um numero inteiro\n");
		}
		if(digit_check(buffer) == true){
		    num_it = atoi(buffer);
		}
	}while(!digit_check(buffer));

	do{
		printf("\nOpcao de vizinhanca (1 = 2vz ; 2 = 4vz ; 3 = 6vz): ");
        scanf("%d", &var);
		if(var != 1 && var != 2 && var != 3){
			printf("\nOpcao escolhida invalida\n");
		}

	}while(var != 1 && var != 2 && var != 3);
			
	
	if(runs <= 0)
		return 0;
	init_rand();
    // Preenche matriz de adjacencias
    grafo = init_dados(nome_fich, &vert , &kV);
	sol = malloc(sizeof(int)*vert);
	best = malloc(sizeof(int)*vert);
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	for(k=0; k<runs; k++)
	{
		// Gerar solucao inicial

		gera_sol_inicial(sol, vert, kV);

		escreve_sol(sol, vert);



		// Trepa colinas
		custo = trepa_colinas(sol, grafo, vert, num_it);
		// Escreve resultados da repeticao k
		printf("\nRepeticao %d:", k);
		escreve_sol(sol, vert);
		printf("Custo final: %2d\n", custo);
		mbf += custo;
		if(k==0 || best_custo < custo)
		{
			best_custo = custo;
			substitui(best, sol, vert);
		}
    }
	// Escreve eresultados globais
	printf("\n\nMBF: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("Custo final: %2d\n", best_custo);
	free(grafo);
    free(sol);
	free(best);
    return 0;
}

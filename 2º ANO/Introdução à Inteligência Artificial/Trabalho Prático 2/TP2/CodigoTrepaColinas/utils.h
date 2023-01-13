#include <stdbool.h>

int* init_dados(char *nome, int *n, int *kV);
void gera_sol_inicial(int *sol, int v, int kV);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
void escreve_matriz(int *matriz, int n);
bool digit_check(char key[]);
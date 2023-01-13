#include <stdbool.h>

struct info init_data(char *s, int mat[][2], int popsize, float pm, float pr, int tsize, int numGenerations, int *grafo);
pchrom init_pop(struct info d);
void print_pop(pchrom pop, struct info d);
chrom get_best(pchrom pop, struct info d, chrom best);
void write_best(chrom x, struct info d);
void write_best_profit(pchrom x, struct info d);
void init_rand();
int random_l_h(int min, int max);
float rand_01();
int flip();
void escreve_matriz(int *matriz, int n);
bool digit_check(char key[]);
bool float_check(char key[]);


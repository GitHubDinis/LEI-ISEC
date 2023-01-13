#include <stdbool.h>
void evaluate(pchrom pop, struct info d, int mat[][2], int * grafo);
float quality(int * sol, struct info d, int mat[][2], int * grafo);

void trepa_colinas(pchrom pop, struct info d, int mat[][2]);
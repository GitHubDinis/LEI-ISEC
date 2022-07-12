#include <stdio.h>
#define TAM 100

int InsereNovaTemperatura(float tempmin[], float tempmax[],int dim, float nova_tmin, float nova_tmax){

    if (nova_tmin < nova_tmax)
        return -1;

    if (nova_tmin > 90 && nova_tmin < -90)
        return -1;
    
    if (nova_tmax > 90 && nova_tmax < -90)
        return -1;

    int i;

    for (i = 0; i < dim-1; i++) {

        tempmin[i+1] = tempmin[i];
    
	}

    tempmin[0] = nova_tmin;

    for (i = 1; i < dim-1; i++) {

        tempmax[i+1] = tempmax[i];
    
	}

    tempmax[0] = nova_tmax;

    return nova_tmax - nova_tmin;
}


/////////////// Pergunta 2 do Exame da Época Normal de IP ///////////////
// Nome: Dinis Meireles de Sousa Falcão
// Nº Estudante: 2020130403

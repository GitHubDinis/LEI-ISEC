#ifndef WORK_RESERVA_H
#define WORK_RESERVA_H

#include <vector>
#include "animais.h"
#include "alimentos.h"

class reserva{
    int nl;
    int nc;
    vector<animal> vAnimais;
    vector<alimentos> vAlimentos;

public:
    static void printGrid(int &nl, int &nc);
    static int print();
    void adicionaAnimais(animal a);
    void adicionaAlimentos(alimentos as);
    string getAsStringA();
    string getAsStringAli();
};

#endif //WORK_RESERVA_H

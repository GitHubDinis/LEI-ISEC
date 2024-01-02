#ifndef NEWWORKPOO_SIMULADOR_H
#define NEWWORKPOO_SIMULADOR_H

#include <vector>
#include <map>
#include <fstream>

#include "Terminal.h"
#include "Habitacao.h"

using namespace term;

class Simulador {
public:
    Simulador();
    ~Simulador();

    void iniciaInterface();

    void avancaIteration(int n = 1);

    string validaComandos(const string& recebe);

    bool validaString(const string& str);
private:
    Habitacao *habitacaoAtual = nullptr;

    Window *windowHabit = nullptr;

    map<int, Window*> windowsMap;

    Window *windowZona11 = nullptr;
    Window *windowZona12 = nullptr;
    Window *windowZona13 = nullptr;
    Window *windowZona14 = nullptr;
    Window *windowZona21 = nullptr;
    Window *windowZona22 = nullptr;
    Window *windowZona23 = nullptr;
    Window *windowZona24 = nullptr;
    Window *windowZona31 = nullptr;
    Window *windowZona32 = nullptr;
    Window *windowZona33 = nullptr;
    Window *windowZona34 = nullptr;
    Window *windowZona41 = nullptr;
    Window *windowZona42 = nullptr;
    Window *windowZona43 = nullptr;
    Window *windowZona44 = nullptr;

    Window *windowOutput = nullptr;

    int iteration = 0;
};


#endif //NEWWORKPOO_SIMULADOR_H

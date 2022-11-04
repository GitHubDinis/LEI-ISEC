#ifndef UNTITLED19_ARQUIVO_H
#define UNTITLED19_ARQUIVO_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include <initializer_list>

using namespace std;

class Televisao{
    static const int MAX_CANAIS = 10;
    vector<string> canais;
    bool ligada;
    int som;
    int canalActual;
    int numCanais = 0;

public:
    Televisao(initializer_list<string> ca);
    void LigarTV();
    void DesligarTV();
    void AumentarVolume();
    void DiminuirVolume();
    void MudarCanal();
};

#endif //UNTITLED19_ARQUIVO_H
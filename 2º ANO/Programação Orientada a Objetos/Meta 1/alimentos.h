#ifndef WORK_ALIMENTOS_H
#define WORK_ALIMENTOS_H

#pragma once
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

class alimentos{
    int duracao;
    int valorNutritivo;
    int toxicidade;
    bool consumido;
    vector<string> cheiros;

public:
    alimentos(int d, int vn, int t, bool c): duracao(d), valorNutritivo(vn), toxicidade(t), consumido(c){};
    //alimentos(initializer_list<string> ch);
    bool adicionaCheiro(string cheiro);
    int getVN() const;
    int getToxic() const;
};

#endif //WORK_ALIMENTOS_H

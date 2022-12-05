#ifndef WORK_ANIMAIS_H
#define WORK_ANIMAIS_H

#include <string>

using namespace std;

class animal{
    string especie;
    string nome;
    int id;
    int saude;
    int distpercepcao;
    int peso;
    int fome;
    int agressividade;
    int tempoVida;
    bool vida;
    int posY, posX;

public:
    animal(int id, string nome, string especie, int posX, int posY, bool vida, int tempoVida, int saude, int distpercepcao, int agressividade, int peso, int fome) :id(id), nome(nome), especie(especie), posX(posX), posY(posY), vida(vida), tempoVida(tempoVida), saude(saude), distpercepcao(distpercepcao), agressividade(agressividade), peso(peso), fome(fome) {}

    int getX() const;
    int getY() const;
    int getID() const;
    string getEsp() const;
    int getSaude() const;
};

#endif //WORK_ANIMAIS_H
#ifndef NEWWORKPOO_PROCESSADOR_H
#define NEWWORKPOO_PROCESSADOR_H

#include <iostream>
#include <vector>

#include "Componente.h"
#include "Aparelho.h"
#include "Regra.h"
#include "Regras/Entre.h"
#include "Regras/Fora.h"
#include "Regras/IgualA.h"
#include "Regras/MaiorQue.h"
#include "Regras/MenorQue.h"

using namespace std;

class Processador : public Componente {
public:
    Processador(string comando);
    ~Processador() override;
    Processador(const Processador &outro);

    bool adicionaRegra(Regra *novaRegra);
    bool removeRegra(int ID);

    bool associaAparelho(Aparelho *novoAparelho);
    bool removeAparelho(int IDaparelho);

    string listaRegras() const;

    bool avaliaResultadoRegras() const;

    void avancaIteration();

    string getAsString() const override;

    string getNomeCopia() const;
    void setNomeCopia(string novoNome);

    int getIDzonaCopia() const;
    void setIDzonaCopia(int ID);

    Processador* clone() const override;
private:
    string comando;
    int numeroRegras = 0, IDzonaCopia = 0;
    vector<Regra *> regras;
    vector<Aparelho*> aparelhos;
    string nomeCopia = " ";
};

#endif //NEWWORKPOO_PROCESSADOR_H
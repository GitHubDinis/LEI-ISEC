#ifndef NEWWORKPOO_HABITACAO_H
#define NEWWORKPOO_HABITACAO_H

#include <iostream>
#include <sstream>

#include "Zona.h"

using namespace std;

class Habitacao {
public:
    Habitacao(int linhas, int colunas);
    ~Habitacao();

    bool adicionaZona(int linha, int coluna);
    bool removeZona(int IDzona);

    string listaComponentes(int IDzona);
    string listaPropriedades(int IDzona);

    void modificaValorPropriedade(int IDzona, string nome, float valor);

    bool adicionaComponente(int IDzona, char letra, string tipoOuComando);
    bool removeComponente(int IDzona, char letra, int IDcomponente);

    bool mudaComandoProcessador(int IDzona, int IDcomponente, string novoComando);

    bool criaRegra(int IDzona, int IDprocessador, string tipoRegra, int IDsensor, float param1, float param2);
    bool criaRegra(int IDzona, int IDprocessador, string tipoRegra, int IDsensor, float param1);

    string listaRegras(int IDzona, int IDprocessador) const;

    bool removeRegra(int IDzona, int IDprocessador, int IDregra);

    bool associaProcessadorAparelho(int IDzona, int IDprocessador, int IDaparelho);
    bool desassociaProcessadorAparelho(int IDzona, int IDprocessador, int IDaparelho);

    int getIDzona() const;

    int getLinhas() const;
    int getColunas() const;

    void avancaIteration();

    void enviaComandoManual(int IDzona, int IDaparelho, string comando);

    string getAsString() const;

    string colocaLetra(int IDzona, int IDcomponente);
    string colocaLetrasTodas(int IDzona);

    void copiarProcessador(int IDzona, int IDprocessador, string novoNome);
    void ativarCopiasProcessador(string nome);
    bool apagaCopiaProcessador(string nome);
    int retornaIDcopia(string nome);

    string listaCopiasProcessador() const;
private:
    int linhas, colunas;
    vector<Processador *> copiasProcessadores;
    vector<Zona *> zonas;
};


#endif //NEWWORKPOO_HABITACAO_H

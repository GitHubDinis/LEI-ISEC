#ifndef NEWWORKPOO_ZONA_H
#define NEWWORKPOO_ZONA_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

#include "Componente.h"
#include "Sensor.h"
#include "Processador.h"
#include "Aparelho.h"
#include "Aparelhos/Aquecedor.h"
#include "Aparelhos/Aspersor.h"
#include "Aparelhos/Lampada.h"
#include "Aparelhos/Refrigerador.h"
#include "Propriedade.h"
#include "Propriedades/Fumo.h"
#include "Propriedades/Humidade.h"
#include "Propriedades/Luz.h"
#include "Propriedades/Radiacao.h"
#include "Propriedades/Som.h"
#include "Propriedades/Temperatura.h"
#include "Propriedades/Vibracao.h"

#include "Regras/Entre.h"
#include "Regras/Fora.h"
#include "Regras/IgualA.h"
#include "Regras/MaiorQue.h"
#include "Regras/MenorQue.h"

using namespace std;

class Zona {
public:
    Zona(int linha, int coluna);
    ~Zona();

    int getLinha() const;
    int getColuna() const;
    int getID() const;

    string listaComponentes() const;
    string listaPropriedades() const;

    bool modificaPropriedade(string nome, float valor);

    bool adicionaComponente(char letra, string tipoOuComando);
    void adicionarPropriedades();
    void contaComponentes();

    bool mudaComandoProcessador(int IDcomponente, string novoComando);

    bool removeComponente(char letra, int IDcomponente);

    bool criaRegra(int IDprocessador, string tipoRegra, int IDsensor, float param1, float param2);
    bool criaRegra(int IDprocessador, string tipoRegra, int IDsensor, float param1);

    string listaRegras(int IDprocessador) const;

    bool removeRegra(int IDprocessador, int IDregra);

    bool associaProcessadorAparelho(int IDprocessador, int IDaparelho);
    bool desassociaProcessadorAparelho(int IDprocessador, int IDaparelho);

    Propriedade *retornaPropriedade(string tipo);
    Sensor *retornaSensor(int ID);
    Processador *retornaProcessador(int ID);
    Aparelho *retornaAparelho(int ID);

    void avancaIteration();

    void enviaComandoManual(int IDaparelho, string comando);

    string getAsString();

    string colocaLetra(int IDcomponente);
    string colocaLetrasTodas();

    Processador * copiarProcessador(int IDzona, int IDprocessador, string novoNome);
    void ativarCopiasProcessador(string nome);
private:
    int ID;
    int linha, coluna;
    int nProcessadores = 0, nSensores = 0, nAparelhos = 0;

    vector<Componente *> componentes;

    vector<Aparelho *> aparelhos;
    vector<Processador *> processadores;
    vector<Processador *> copiasProcessadores;
    vector<Sensor *> sensores;

    vector<Regra *> regras;

    vector<Propriedade *> propriedades;
};

#endif //NEWWORKPOO_ZONA_H
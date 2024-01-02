//
// Created by Utilizador on 09/12/2023.
//

#include "Habitacao.h"

Habitacao::Habitacao(int linhas, int colunas) : linhas(linhas), colunas(colunas) {
    if (linhas < 2 || linhas > 4 || colunas < 2 || colunas > 4) {
        throw invalid_argument("Dimension deve ser entre 2x2 e 4x4.");
    }
    cout << "Construtor de Habitacao!" << endl;
}

Habitacao::~Habitacao() {
    for(auto zona : zonas)
        delete zona;
    zonas.clear();

    cout << "Destrutor de Habitacao!" << endl;
}

bool Habitacao::adicionaZona(int linha, int coluna) {
    if(linha > this->linhas || coluna > this->colunas || linha < 1 || coluna < 1){
        return false;
    }
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getLinha() == linha && (*it)->getColuna() == coluna)
            return false;
        it++;
    }

    Zona *novaZona = new Zona(linha, coluna);
    zonas.push_back(novaZona);

    return true;
}

bool Habitacao::removeZona(int IDzona) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            zonas.erase(it);
            return true;
        }
        it++;
    }

    return false;
}

string Habitacao::listaComponentes(int IDzona) {
    ostringstream buffer0;
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            buffer0 << (*it)->listaComponentes();
        }
        it++;
    }
    return buffer0.str();
}

string Habitacao::listaPropriedades(int IDzona) {
    ostringstream buffer0;
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            buffer0 << (*it)->listaPropriedades();
        }
        it++;
    }
    return buffer0.str();
}

void Habitacao::modificaValorPropriedade(int IDzona, string nome, float valor) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->modificaPropriedade(nome, valor);
        }
        it++;
    }
}

bool Habitacao::adicionaComponente(int IDzona, char letra, string tipoOuComando) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->adicionaComponente(letra, tipoOuComando);
            return true;
        }
        it++;
    }
    return false;
}

bool Habitacao::removeComponente(int IDzona, char letra, int IDcomponente) {
    auto it = zonas.begin();
    while (it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->removeComponente(letra, IDcomponente);
            return true;
        }
        it++;
    }
    return false;
}

string Habitacao::getAsString() const {
    ostringstream buffer0;
    auto it = zonas.begin();
    while(it < zonas.end()){
        buffer0 << (*it)->getAsString() << endl;
        it++;
    }
    return buffer0.str();
}

int Habitacao::getLinhas() const {
    return this->linhas;
}

int Habitacao::getColunas() const {
    return this->colunas;
}

bool Habitacao::mudaComandoProcessador(int IDzona, int IDcomponente, string novoComando) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->mudaComandoProcessador(IDcomponente, novoComando);
        }
        it++;
    }
    return false;
}

bool Habitacao::criaRegra(int IDzona, int IDprocessador, string tipoRegra, int IDsensor, float param1, float param2) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->criaRegra(IDprocessador, tipoRegra, IDsensor, param1, param2);
        }
        it++;
    }
    return false;
}

bool Habitacao::criaRegra(int IDzona, int IDprocessador, std::string tipoRegra, int IDsensor, float param1) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->criaRegra(IDprocessador, tipoRegra, IDsensor, param1);
            return true;
        }
        it++;
    }
    return false;
}

string Habitacao::listaRegras(int IDzona, int IDprocessador) const {
    ostringstream buffer0;
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            buffer0 << (*it)->listaRegras(IDprocessador) << endl;
        }
        it++;
    }
    return buffer0.str();
}

bool Habitacao::removeRegra(int IDzona, int IDprocessador, int IDregra) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->removeRegra(IDprocessador, IDregra);
            return true;
        }
        it++;
    }
    return false;
}

bool Habitacao::associaProcessadorAparelho(int IDzona, int IDprocessador, int IDaparelho) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->associaProcessadorAparelho(IDprocessador, IDaparelho);
            return true;
        }
        it++;
    }
    return false;
}

bool Habitacao::desassociaProcessadorAparelho(int IDzona, int IDprocessador, int IDaparelho) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            (*it)->desassociaProcessadorAparelho(IDprocessador, IDaparelho);
            return true;
        }
        it++;
    }
    return false;
}

void Habitacao::avancaIteration() {
    auto it = zonas.begin();
    while(it < zonas.end()){
        (*it)->avancaIteration();
        it++;
    }
}

void Habitacao::enviaComandoManual(int IDzona, int IDaparelho, string comando) {
    auto it = zonas.begin();
    while(it < zonas.end()){
        (*it)->enviaComandoManual(IDaparelho, comando);
        it++;
    }
}

string Habitacao::colocaLetra(int IDzona, int IDcomponente) {
    ostringstream buffer0;
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            buffer0 << (*it)->colocaLetra(IDcomponente);
        }
        it++;
    }
    return buffer0.str();
}

string Habitacao::colocaLetrasTodas(int IDzona) {
    ostringstream buffer0;
    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            buffer0 << (*it)->colocaLetrasTodas();
        }
        it++;
    }
    return buffer0.str();
}

void Habitacao::copiarProcessador(int IDzona, int IDprocessador, string novoNome) {
    auto itC = copiasProcessadores.begin();
    while(itC < copiasProcessadores.end()){
        if((*itC)->getNomeCopia() == novoNome){
            return;
        }
        itC++;
    }

    auto it = zonas.begin();
    while(it < zonas.end()){
        if((*it)->getID() == IDzona){
            copiasProcessadores.push_back((*it)->copiarProcessador(IDzona, IDprocessador, novoNome));
        }
        it++;
    }
}

void Habitacao::ativarCopiasProcessador(string nome) {
    auto it = copiasProcessadores.begin();
    while(it < copiasProcessadores.end()){
        if((*it)->getNomeCopia() == nome){
            auto itZ = zonas.begin();
            while(itZ < zonas.end()){
                if((*itZ)->getID() == (*it)->getIDzonaCopia()){
                    (*itZ)->ativarCopiasProcessador(nome);
                }
                itZ++;
            }
        }
        it++;
    }
}

bool Habitacao::apagaCopiaProcessador(string nome) {
    auto it = copiasProcessadores.begin();
    while(it < copiasProcessadores.end()){
        if((*it)->getNomeCopia() == nome){
            copiasProcessadores.erase(it);
        }
        it++;
    }

    return false;
}

string Habitacao::listaCopiasProcessador() const {
    ostringstream buffer0;
    auto it = copiasProcessadores.begin();
    while(it < copiasProcessadores.end()){
        buffer0 << "Nome: " << (*it)->getNomeCopia() << ", ID Processador: " << (*it)->getIDnum() << ", ID zona: " << (*it)->getIDzonaCopia() << endl;
        it++;
    }
    return buffer0.str();
}

int Habitacao::retornaIDcopia(string nome) {
    auto it = copiasProcessadores.begin();
    while(it < copiasProcessadores.end()){
        if((*it)->getNomeCopia() == nome){
            return (*it)->getIDzonaCopia();
        }
    }
    return 0;
}

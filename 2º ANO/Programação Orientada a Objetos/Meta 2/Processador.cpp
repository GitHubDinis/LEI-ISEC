#include "Processador.h"

Processador::Processador(string comando) : Componente('p', "processador", comando), comando(comando) {
    auto it = aparelhos.begin();
    while (it < aparelhos.end()){
        *it = nullptr;
    }
    cout << "Construtor de Processador de Regras!" << endl;
}

Processador::~Processador() {
    for (auto regra : regras)
        delete regra;
    regras.clear();
    for (auto aparelho : aparelhos)
        delete aparelho;
    aparelhos.clear();
    cout << "Destrutor de Processador de Regras!" << endl;
}

Processador::Processador(const Processador &outro) : Componente(outro), comando(outro.comando), numeroRegras(outro.numeroRegras), IDzonaCopia(outro.IDzonaCopia) {
    for (const Regra *regra : outro.regras) {
        this->regras.push_back(regra->clone());
    }

    for (const Aparelho *aparelho : outro.aparelhos) {
        this->aparelhos.push_back(aparelho->clone());
    }

    this->nomeCopia = outro.nomeCopia;

    cout << "Construtor por Cópia do Processador de Regras!" << endl;
}

bool Processador::avaliaResultadoRegras() const {
    auto it = regras.begin();
    while(it < regras.end()){
        if((*it)->check() == false){
            return false;
        }
        it++;
    }

    return true;
}

bool Processador::adicionaRegra(Regra *novaRegra) {
    this->regras.push_back(novaRegra);
    this->numeroRegras++;
    return true;
}

string Processador::listaRegras() const {
    ostringstream buffer0;
    auto it = regras.begin();
    while(it < regras.end()){
        buffer0 << "Nome: " << (*it)->getNome() << ", ID: " << (*it)->getID() << ", Nome Sensor: " << (*it)->getNomeSensor() << ", ID Sensor: " << (*it)->getIDSensor();
        it++;
    }
    return buffer0.str();
}

bool Processador::removeRegra(int ID) {
    auto it = regras.begin();
    while(it < regras.end()){
        if((*it)->getID() == ID){
            regras.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool Processador::associaAparelho(Aparelho *novoAparelho) {
    aparelhos.push_back(novoAparelho);
    return true;
}

bool Processador::removeAparelho(int IDaparelho) {
    auto it = aparelhos.begin();
    while(it < aparelhos.end()){
        if((*it)->getIDnum() == IDaparelho){
            aparelhos.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

void Processador::avancaIteration() {
    if(this->avaliaResultadoRegras() == true){
        auto it = aparelhos.begin();
        while(it < aparelhos.end()){
            if(this->getTipoOuComando() == (*it)->getComandoReconhecido(0)){
                if((*it)->getLigado() == true){
                    (*it)->efeitoSeLigado();
                } else if((*it)->getLigado() == false){
                    (*it)->efeitoSeLigado();
                    (*it)->setLigado(true);
                }
            } else if(this->getTipoOuComando() == (*it)->getComandoReconhecido(1)){
                if((*it)->getLigado() == true){
                    (*it)->efeitoAoDesligar();
                    (*it)->setLigado(false);
                } else if((*it)->getLigado() == false){
                    return;
                }
            }
            it++;
        }
    } else{

    }
}

string Processador::getAsString() const {
    ostringstream buffer0;
    string soma = this->getLetra() + to_string(this->getIDnum());
    buffer0 << "Tipo: " << soma << ", Nome: processador" << ", Regras: " << this->numeroRegras << endl;
    return buffer0.str();
}

string Processador::getNomeCopia() const {
    return this->nomeCopia;
}

void Processador::setNomeCopia(string novoNome) {
    this->nomeCopia = novoNome;
}

int Processador::getIDzonaCopia() const {
    return this->IDzonaCopia;
}

void Processador::setIDzonaCopia(int ID) {
    this->IDzonaCopia = ID;
}

Processador *Processador::clone() const {
    return new Processador(*this);
}

//
// Created by Utilizador on 30/11/2023.
//

#include "Imobiliaria.h"

Imobiliaria::Imobiliaria(const string &nome) : nome(nome) {
    cout << "A construir Imobiliaria" << endl;
}

Imobiliaria::~Imobiliaria() {
    cout << "A destruir Imobiliaria" << endl;
}

int Imobiliaria::pesquisa(const string &codigo) const {
    int indice = -1;
    for (int i = 0; i < imoveis.size(); i++) {
        if(imoveis.at(i)->getCodigo() == codigo){
            indice = i;
            break;
        }
    }

    return indice;
}

bool Imobiliaria::acrescenta(Imovel *i) {

    int indice = pesquisa(i->getCodigo());

    if(indice == -1){
        imoveis.emplace_back(i);
        return true;
    }

    return false;
}

string Imobiliaria::listaPorAndar(int andar) {
    ostringstream os;
    for(Imovel * i:imoveis){
        if(i->getAndar() == andar){
            os << i->getAsString();
        }
    }
    return os.str();
}

string Imobiliaria::listaPorCodigo(const string &codigo) {
    int indice = pesquisa(codigo);

    if(indice == -1){
        return imoveis.at(indice)->getAsString();
    }

    return "Nao encontrado!";
}

bool Imobiliaria::removePorCodigo(const string &codigo) {
    int indice = pesquisa(codigo);
    if(indice != -1){
        imoveis.erase(imoveis.begin() + indice);
        return true;
    }

    return false;
}

string Imobiliaria::getAsString() const {
    ostringstream os;
    os << "Nome: " << this->nome << ", com " << imoveis.size() << " imoveis em carteira: " << endl;
    for(Imovel * i:imoveis){
            os << i->getAsString();
    }
    return os.str();
}

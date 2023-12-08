//
// Created by Utilizador on 30/11/2023.
//

#include "Imovel.h"

int Imovel::contador = 0;

Imovel::Imovel(float preco, int area, int andar, const string &tipo) : andar(andar), area(area), preco(preco), tipo(tipo) {
    ostringstream os;
    os << tipo << ++contador;
    codigo = os.str();
    cout << "A construir Imovel" << endl;
}

Imovel::~Imovel() {
    cout << "A destruir Imovel" << endl;
}

const string &Imovel::getCodigo() const {
    return this->codigo;
}

float Imovel::getPreco() const {
    return this->preco;
}

int Imovel::getAndar() const {
    return this->andar;
}

string Imovel::getAsString() const {
    ostringstream os;
    os << "Codigo: " << this->codigo << ", Preco: " << this->preco << "€, Area: " << this->area << "m2, Andar: " << this->andar << ", Tipo: " << this->tipo << endl;
    return os.str();
}

ostream &operator<<(ostream &o, const Imovel &im){
    o << im.getAsString();
    return o;
}
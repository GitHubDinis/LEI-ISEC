//
// Created by Utilizador on 30/11/2023.
//

#include "RegistoPredial.h"



RegistoPredial::~RegistoPredial() {
    for (Imovel *el: imoveis) {
        delete el;
    }
}

bool RegistoPredial::acrescenta(Imovel *im) {
    imoveis.emplace_back(im); // EXEMPLO
    return true;
}

Imovel *RegistoPredial::pesquisa(const string &cod) {
    for (int i = 0; i < imoveis.size(); i++) {
        if(imoveis.at(i)->getCodigo() == cod){
            return imoveis.at(i);
        }
    }

    return nullptr;
}
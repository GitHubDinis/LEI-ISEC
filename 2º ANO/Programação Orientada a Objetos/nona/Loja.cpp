//
// Created by Utilizador on 30/11/2023.
//

#include "Loja.h"

Loja::Loja(int area) : Imovel(15.0 * area, area, 0, "Loja"){
    cout << "A construir Loja" << endl;
}

Loja::~Loja() {
    cout << "A destruir Loja" << endl;
}

//
// Created by Utilizador on 21/12/2023.
//
#include <iostream>
#include <memory>

#include "Ponto.h"

using namespace std;

int main(){
    unique_ptr<Ponto> up1 = make_unique<Ponto>(1,1);
    unique_ptr<Ponto> up2 = make_unique<Ponto>(2,2);
    //up1 = up2;
    //swap(up1, up2);
    up1 = std::move(up2);
    up1->mostra();
    shared_ptr<Ponto> sp1 = make_shared<Ponto>(3,3);
    shared_ptr<Ponto> sp2 = make_shared<Ponto>(4,4);
    sp1 = sp2;
    shared_ptr<Ponto> partilhado1 = make_shared<Ponto>(5,5);
    shared_ptr<Ponto> partilhado2 = make_shared<Ponto>(6,6);
    weak_ptr<Ponto> wp1 = partilhado1;
    weak_ptr<Ponto> wp2 = partilhado2;
    wp1 = wp2;

    return 0;
}
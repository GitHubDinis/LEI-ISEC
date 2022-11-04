#include <iostream>
#include <sstream>
#include <string>
#include <initializer_list>

#include "Televisao.h"

using namespace std;

Televisao::Televisao(initializer_list<string> ca){

    for (auto c : ca) {
        if(numCanais < MAX_CANAIS){
            canais.push_back(c);
            numCanais++;
        }
    }
    ligada = false;
    som = 5;

    if(!canais.empty())
        canalActual = 1;
}

void Televisao::LigarTV(){

    if(!ligada) {
        ligada = true;
        cout << "-- On -- \n";
    }
    else
        cout << "Televisao ja se encontra Ligada!\n";
}

void Televisao::DesligarTV(){
    if(ligada) {
        ligada = false;
        cout << "-- Off -- \n";
    }
    else
        cout << "Televisao ja se encontra Desligada!\n";
}

void Televisao::AumentarVolume(){
    if(ligada){
        ligada = true;
        if(som < 10) {
            som++;
            cout << "Volume aumentado para \n" << som;
        }
    }
}

void Televisao::DiminuirVolume(){
    if(ligada){
        ligada = true;
        if(som > 0) {
            som--;
            cout << "Volume diminuido para \n" << som;
        }
    }
}

void Televisao::MudarCanal(){

}
#include <iostream>
#include "interface.h"
#include "reserva.h"

using namespace std;

int main(){
    cout << "Bem-Vindo ao Simulador da Reserva Natural!" << endl << endl;

    interface::leFicheiro();

    cout << endl << endl;

    reserva::print();

    /*reserva r;
    animal a(1,"ola","ola", 2,3,true,20,12,12,12,12,12);
    alimentos o(10,10,10, false);

    r.print();
    r.adicionaAnimais(a);
    r.adicionaAlimentos(o);
    cout << "\n" << r.getAsString();*/

    cout << endl << endl;

    interface::recebeComandos();
}


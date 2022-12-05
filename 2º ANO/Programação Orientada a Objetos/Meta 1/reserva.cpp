#include "reserva.h"
#include <iostream>
#include <sstream>

using namespace std;

void reserva::printGrid(int &nl, int &nc) {
    cout << endl;
    cout << " ";
    int i=0,j;
    for(j = 0; j <= 4*nc; j++){
        if(j%4==2)
            cout<<i++;
        else cout<<" ";
    }
    cout<<endl;
    for(i = 0; i <= 2*nl; i++){
        if(i%2!=0)
            cout<<(char)(i/2 +'A');
        for(j = 0; j <= 2*nc; j++){
            if(i%2==0)
            {
                if(j==0)
                    cout<<" ";
                if(j%2==0)
                    cout<<" ";
                else cout<<"---";
            }
            else{
                if(j%2==0)
                    cout<<"|";
                else cout<<"   ";
            }
        }
        if(i%2!=0)
            cout<<(char)(i/2 +'A');
        cout<<endl;
    }
    cout<<" ";
    for(j = 0, i = 0; j <= 4*nc; j++){
        if(j%4==2)
            cout<<i++;
        else cout<<" ";
    }
    cout<<endl;
}

int reserva::print() {
    int nl, nc;
    cout << "Enter the number of rows -> ";
    cin >> nl;
    cout << "Enter the number of columns -> ";
    cin >> nc;
    printGrid(nl, nc);
    return 0;
}

void reserva::adicionaAnimais(animal a) {
    this->vAnimais.push_back(a);
}

void reserva::adicionaAlimentos(alimentos as) {
    this->vAlimentos.push_back(as);
}

string reserva::getAsStringA(){

    ostringstream os;

    auto i = this->vAnimais.begin();
    while(i != this->vAnimais.end()){
        os << "ID: " << i->getID() << " Especie: " << i->getEsp() << " Saude: " << i->getSaude() << endl;
        ++i;
    }
    return os.str();
}

string reserva::getAsStringAli(){

    ostringstream os;

    auto i = this->vAlimentos.begin();
    while(i != this->vAlimentos.end()){
        os << "Valor Nutritivo: " << i->getVN() << " Toxicidade: " << i->getToxic() << endl;
        ++i;
    }
    return os.str();
}
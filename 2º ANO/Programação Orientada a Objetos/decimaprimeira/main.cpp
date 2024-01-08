#include <iostream>
#include <memory>

#include "Ponto.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    // zona inicial
    {
        // BLOCO B1
        unique_ptr<Ponto> spw = make_unique<Ponto>(4,4);
    }
    {
        // BLOCO B2
        shared_ptr<Ponto> sps1 = make_shared<Ponto>(2, 3);
        sps1->mostra();
        spw = sps1;
        cout << sps2.use_count() << endl;
        if(sps2 == nullptr)
            cout << "Este shared pointer não está a apontar para nada \n";

        sps2 = sps1; // SE ESTIVER COMENTADO, SPS2 É APAGADO
        cout << sps1.use_count();
        if(auto obj = spw.lock())
            obj.mostra();
        cout << "Antes de acabar o bloco 2!\n";
    }
    cin.get();
    {
        // BLOCO B3
        cout << "No Bloco 3\n";
        unique_ptr<Ponto[]> arrayU = make_unique<Ponto[]>(10);
        shared_ptr<Ponto[]> arrayS = make_shared<Ponto[]>(10);
        weak_ptr<Ponto[]> arrayW;
        arrayW = arrayS;
        for (int i = 0; i < 10; i++) {
            cout << "Unique: ";
            arrayU[i].mostra();
        }
        for (int i = 0; i < 10; i++) {
            cout << "Unique: ";
            arrayS[i].mostra();
        }
        if(auto obj = arrayW.lock())
            for (int i = 0; i < 10; i++) {
                cout << "Atraves do weak: ";
                obj[i].mostra();
            }
        if(arrayW.expired())
            cout << "Ponteiro weak está expired!";
    }

    return 0;
}

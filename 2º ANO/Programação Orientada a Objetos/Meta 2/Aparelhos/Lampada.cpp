#include "Lampada.h"

static int contaIt = 1;

Lampada::Lampada(vector<Propriedade*> propriedades) : Aparelho(propriedades, "lampada", 'l'), propriedades(propriedades) {
    cout << "Construtor de Aparelho Lampada!" << endl;
}

Lampada::~Lampada() {
    cout << "Destrutor de Aparelho Lampada!" << endl;
}

Lampada::Lampada(const Lampada &outro) : Aparelho(outro.propriedades, outro.getTipoOuComando(), outro.getLetra()), propriedades(outro.propriedades) {

}

void Lampada::efeitoSeLigado() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if(contaIt == 1){
            if((*it)->getNome() == "luz"){
                (*it)->setValor((*it)->getValor() + 900);
            }
        }
        it++;
    }
    contaIt++;
}

void Lampada::efeitoAoDesligar() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if((*it)->getNome() == "luz"){
            (*it)->setValor((*it)->getValor() - 900);
            if((*it)->getValor() < 0){
                (*it)->setValor(0);
            }
            contaIt = 1;
        }
        it++;
    }
}

Lampada *Lampada::clone() const {
    return new Lampada(*this);
}

#include "Aquecedor.h"

static int contaIt = 1;

Aquecedor::Aquecedor(vector<Propriedade*> propriedades) : Aparelho(propriedades, "aquecedor", 'a'), propriedades(propriedades) {
    cout << "Construtor de Aparelho Aquecedor!" << endl;
}

Aquecedor::~Aquecedor() {
    cout << "Destrutor de Aparelho Aquecedor!" << endl;
}

Aquecedor::Aquecedor(const Aquecedor &outro) : Aparelho(outro.propriedades, outro.getTipoOuComando(), outro.getLetra()), propriedades(outro.propriedades) {

}

void Aquecedor::efeitoSeLigado() {
    if(contaIt > 150){
        contaIt = 1;
    }
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if(contaIt >= 3){
            if(contaIt % 3 == 0){
                if((*it)->getNome() == "temperatura") {
                    (*it)->setValor((*it)->getValor() + 1);
                }
            }
        } else if(contaIt == 1){
            if((*it)->getNome() == "som"){
                    (*it)->setValor((*it)->getValor() + 5);
            }
        }
        it++;
    }
    contaIt++;
}

void Aquecedor::efeitoAoDesligar() {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if((*it)->getNome() == "som"){
            (*it)->setValor((*it)->getValor() - 5);
            if((*it)->getValor() < 0){
                (*it)->setValor(0);
            }
            contaIt = 1;
        }
        it++;
    }
}

Aquecedor *Aquecedor::clone() const {
    return new Aquecedor(*this);
}


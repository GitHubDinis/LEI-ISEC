#include <iostream>
#include <sstream>
#include <string>
#include <initializer_list>

#include "alimentos.h"

using namespace std;

/*alimentos::alimentos(initializer_list<std::string> ch) {
    for(const auto& c : ch){
        if(cheiros.begin() < cheiros.end()) {
            cheiros.push_back(c);
        }
    }

    if(!cheiros.empty()){

    }
}*/

bool alimentos::adicionaCheiro(std::string cheiro) {
    this->cheiros.push_back(cheiro);

    return true;
}

int alimentos::getVN() const {
    return valorNutritivo;
}

int alimentos::getToxic() const {
    return toxicidade;
}
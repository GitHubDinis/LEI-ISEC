#include "Simulador.h"

static int contaID = 1;
static int contaIDcomponente = 1;

Simulador::Simulador() {
    // cout << "Construtor de Simulador!" << endl;
}

Simulador::~Simulador() {
    delete habitacaoAtual;
    // cout << "Destrutor de Simulador!" << endl;
}

void Simulador::iniciaInterface() {
    Terminal &t = Terminal::instance();

    std::string str_in;

    Window w1 = Window(5, 40, 204, 4);
    windowOutput = new Window(155, 5, 54, 35);

    while(str_in != "sair") {
        w1 << "Comando: ";
        w1 >> str_in;
        w1.clear();
        windowOutput->operator<<(validaComandos(str_in));
    }
}

string Simulador::validaComandos(const std::string &recebe) {
    ostringstream buffer0;

    stringstream str(recebe);
    stringstream convert;
    string token;
    int count = 0, num = 0, num2 = 0, num3 = 0;
    float numF = 0.0;
    char ch = ' ';

    str >> token;
    count++;

    if(token == "prox" && count == 1){
        while(str >> token) {
            count++;
            if(count == 2){
                buffer0 << "[ERRO] Argumentos Incorret!" << endl;
            }
        }
        if(count == 1){
            avancaIteration();
            for (int i = 1; i < contaID; i++) {
                windowsMap[i]->clear();
                windowsMap[i]->operator<<(" " + to_string(i) + "\n ");
                windowsMap[i]->operator<<(habitacaoAtual->colocaLetrasTodas(i) + " ");
            }
            buffer0 << "[CMD] Avancou para Iteration: " << this->iteration << endl;
        }
    } else if(token == "avanca" && count == 1){
        int arg1;
        while(str >> token) {
            count++;
            if(count == 2){
                convert << token;
                if (convert >> num) {
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 2){
            avancaIteration(arg1);
            for (int i = 1; i < contaID; i++) {
                windowsMap[i]->clear();
                windowsMap[i]->operator<<(" " + to_string(i) + "\n ");
                windowsMap[i]->operator<<(habitacaoAtual->colocaLetrasTodas(i) + " ");
            }
            buffer0 << "[CMD] Avancou para Iteration: " << this->iteration << endl;
        } else {
            buffer0 << "[ERRO] Argumentos Incorret!" << endl;
        }
    } else if(token == "hnova" && count == 1){
        int arg1, arg2;
        while(str>>token){
            count++;
            if(count == 2){
                convert << token;
                if (convert >> num) {
                    if(num > 4 || num < 2){
                        buffer0 << "[ERRO] Argumento Invalid [2, 4]!" << endl;
                        return buffer0.str();
                    }
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert2;
                convert2 << token;
                if (convert2 >> num) {
                    if(num > 4 || num < 2){
                        buffer0 << "[ERRO] Argumento Invalid [2, 4]!" << endl;
                        return buffer0.str();
                    }
                    arg2 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 3) {
            buffer0 << "[CMD] Cria Habitacao: " << arg1 << "x" << arg2 << endl;
            habitacaoAtual = new Habitacao(arg1, arg2);
            windowHabit = new Window(5, 5, 150, 35);
            auto it = windowsMap.begin();
            if (it != windowsMap.end()) {
                delete it->second;
                windowsMap.erase(it);
            }
            contaID = 1;
        } else{
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "hrem" && count == 1){
        while(str >> token) {
            count++;
            if(count == 2){
                buffer0 << "[ERRO] Argumento Invalid!" << endl;
            }
        }
        if(count == 1){
            if (habitacaoAtual) {
                delete habitacaoAtual;
                habitacaoAtual = nullptr;
            }
            windowHabit->clear();
            // FALTA APAGAR A WINDOW (retirar o retângulo).
            contaID = 1;
            buffer0 << "[CMD] Removeu Habitacao!" << endl;
        } else {
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "znova" && count == 1){
        int arg1, arg2;
        while(str>>token){
            count++;
            if(count == 2){
                convert << token;
                if (convert >> num) {
                    if(num < 1 || num > habitacaoAtual->getLinhas()){
                        buffer0 << "[ERRO] Argumento Invalid [" << habitacaoAtual->getLinhas() << ", " << habitacaoAtual->getColunas() << "]!" << endl;
                        return buffer0.str();
                    }
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert2;
                convert2 << token;
                if (convert2 >> num) {
                    if(num < 1 || num > habitacaoAtual->getColunas()){
                        buffer0 << "[ERRO] Argumento Invalid [" << habitacaoAtual->getLinhas() << ", " << habitacaoAtual->getColunas() << "]!" << endl;
                        return buffer0.str();
                    }
                    arg2 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 3) {
            habitacaoAtual->adicionaZona(arg1, arg2);
            if(habitacaoAtual->getLinhas() == 2 && habitacaoAtual->getColunas() == 2){
                if (arg1 == 1 && arg2 == 1){
                    // if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 71, 16);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 2) {
                    //if(windowZona12 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(81, 6, 71, 16);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 1){
                    //if(windowZona21 == nullptr) {
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 23, 71, 16);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 2){
                    // if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(81, 23, 71, 16);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                }
            } else if(habitacaoAtual->getLinhas() == 2 && habitacaoAtual->getColunas() == 3){
                if (arg1 == 1 && arg2 == 1){
                    // if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 47, 16);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 1 && arg2 == 2) {
                    // if(windowZona12 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(57, 6, 47, 16);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 3){
                    // if(windowZona13 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona13 = new Window(106, 6, 47, 16);
                        windowsMap[contaID] = windowZona13;
                        windowZona13->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 1){
                    // if(windowZona21 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 23, 47, 16);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 2){
                    // if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(57, 23, 47, 16);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 3){
                    //if(windowZona23 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona23 = new Window(106, 23, 47, 16);
                        windowsMap[contaID] = windowZona23;
                        windowZona23->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                }
            } else if(habitacaoAtual->getLinhas() == 3 && habitacaoAtual->getColunas() == 2){
                if (arg1 == 1 && arg2 == 1){
                    //if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 71, 11);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 2) {
                    // if(windowZona12 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(81, 6, 71, 11);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 1){
                    //if(windowZona21 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 17, 71, 11);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 2){
                    //if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(81, 17, 71, 11);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 1){
                    // if(windowZona31 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona31 = new Window(8, 28, 71, 11);
                        windowsMap[contaID] = windowZona31;
                        windowZona31->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 2){
                    //if(windowZona32 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona32 = new Window(81, 28, 71, 11);
                        windowsMap[contaID] = windowZona32;
                        windowZona32->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                }
            } else if(habitacaoAtual->getLinhas() == 3 && habitacaoAtual->getColunas() == 3){
                if (arg1 == 1 && arg2 == 1){
                    //if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 47, 11);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 2) {
                    // if(windowZona12 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(57, 6, 47, 11);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 1 && arg2 == 3){
                    // if(windowZona13 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona13 = new Window(106, 6, 47, 11);
                        windowsMap[contaID] = windowZona13;
                        windowZona13->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 1){
                    // if(windowZona21 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 17, 47, 11);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 2){
                    //if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(57, 17, 47, 11);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 3){
                    //if(windowZona23 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona23 = new Window(106, 17, 47, 11);
                        windowsMap[contaID] = windowZona23;
                        windowZona23->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 1){
                    // if(windowZona31 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona31 = new Window(8, 28, 47, 11);
                        windowsMap[contaID] = windowZona31;
                        windowZona31->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 2){
                    //if(windowZona32 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona32 = new Window(57, 28, 47, 11);
                        windowsMap[contaID] = windowZona32;
                        windowZona32->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 3){
                    // if(windowZona33 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona33 = new Window(106, 28, 47, 11);
                        windowsMap[contaID] = windowZona33;
                        windowZona33->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                }
            } else if(habitacaoAtual->getLinhas() == 3 && habitacaoAtual->getColunas() == 4){
                if (arg1 == 1 && arg2 == 1){
                    // if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 35, 11);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 1 && arg2 == 2) {
                    // if(windowZona12 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(44, 6, 35, 11);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 3){
                    //if(windowZona13 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona13 = new Window(80, 6, 35, 11);
                        windowsMap[contaID] = windowZona13;
                        windowZona13->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 4){
                    // if(windowZona14 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona14 = new Window(116, 6, 35, 11);
                        windowsMap[contaID] = windowZona14;
                        windowZona14->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 1){
                    //if(windowZona21 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 17, 35, 11);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 2){
                    // if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(44, 17, 35, 11);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 3){
                    //if(windowZona23 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona23 = new Window(80, 17, 35, 11);
                        windowsMap[contaID] = windowZona23;
                        windowZona23->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 4){
                    //if(windowZona24 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona24 = new Window(116, 17, 35, 11);
                        windowsMap[contaID] = windowZona24;
                        windowZona24->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 1){
                    // if(windowZona31 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona31 = new Window(8, 28, 35, 11);
                        windowsMap[contaID] = windowZona31;
                        windowZona31->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 2){
                    // if(windowZona32 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona32 = new Window(44, 28, 35, 11);
                        windowsMap[contaID] = windowZona32;
                        windowZona32->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 3){
                    // if(windowZona33 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona33 = new Window(80, 28, 35, 11);
                        windowsMap[contaID] = windowZona33;
                        windowZona33->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 4){
                    //if(windowZona34 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona34 = new Window(116, 28, 35, 11);
                        windowsMap[contaID] = windowZona34;
                        windowZona34->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                }
            } else if(habitacaoAtual->getLinhas() == 4 && habitacaoAtual->getColunas() == 3){
                if (arg1 == 1 && arg2 == 1){
                    // if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 47, 8);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 2) {
                    // if(windowZona12 == nullptr) {
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(57, 6, 47, 8);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 3){
                    // if(windowZona13 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona13 = new Window(106, 6, 47, 8);
                        windowsMap[contaID] = windowZona13;
                        windowZona13->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 1){
                    //if(windowZona21 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 14, 47, 8);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 2){
                    //if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(57, 14, 47, 8);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 3){
                    // if(windowZona23 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona23 = new Window(106, 14, 47, 8);
                        windowsMap[contaID] = windowZona23;
                        windowZona23->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 1){
                    //if(windowZona31 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona31 = new Window(8, 22, 47, 8);
                        windowsMap[contaID] = windowZona31;
                        windowZona31->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 2){
                    // if(windowZona32 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona32 = new Window(57, 22, 47, 8);
                        windowsMap[contaID] = windowZona32;
                        windowZona32->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 3){
                    //if(windowZona33 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona33 = new Window(106, 22, 47, 8);
                        windowsMap[contaID] = windowZona33;
                        windowZona33->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 4 && arg2 == 1) {
                    //if(windowZona41 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona41 = new Window(8, 30, 47, 8);
                        windowsMap[contaID] = windowZona41;
                        windowZona41->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 4 && arg2 == 2) {
                    // if(windowZona42 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona42 = new Window(57, 30, 47, 8);
                        windowsMap[contaID] = windowZona42;
                        windowZona42->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 4 && arg2 == 3) {
                    // if(windowZona43 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona43 = new Window(106, 30, 47, 8);
                        windowsMap[contaID] = windowZona43;
                        windowZona43->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                }
            } else if(habitacaoAtual->getLinhas() == 4 && habitacaoAtual->getColunas() == 4){
                if (arg1 == 1 && arg2 == 1){
                    //if(windowZona11 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona11 = new Window(8, 6, 35, 8);
                        windowsMap[contaID] = windowZona11;
                        windowZona11->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 1 && arg2 == 2) {
                    //if(windowZona12 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona12 = new Window(44, 6, 35, 8);
                        windowsMap[contaID] = windowZona12;
                        windowZona12->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 1 && arg2 == 3){
                    // if(windowZona13 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona13 = new Window(80, 6, 35, 8);
                        windowsMap[contaID] = windowZona13;
                        windowZona13->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 1 && arg2 == 4){
                    // if(windowZona14 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona14 = new Window(116, 6, 35, 8);
                        windowsMap[contaID] = windowZona14;
                        windowZona14->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 1){
                    // if(windowZona21 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona21 = new Window(8, 14, 35, 8);
                        windowsMap[contaID] = windowZona21;
                        windowZona21->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 2){
                    //if(windowZona22 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona22 = new Window(44, 14, 35, 8);
                        windowsMap[contaID] = windowZona22;
                        windowZona22->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 2 && arg2 == 3){
                    //if(windowZona23 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona23 = new Window(80, 14, 35, 8);
                        windowsMap[contaID] = windowZona23;
                        windowZona23->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 2 && arg2 == 4){
                    //if(windowZona24 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona24 = new Window(116, 14, 35, 8);
                        windowsMap[contaID] = windowZona24;
                        windowZona24->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 1){
                    //if(windowZona31 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona31 = new Window(8, 22, 35, 8);
                        windowsMap[contaID] = windowZona31;
                        windowZona31->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 2){
                    //if(windowZona32 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona32 = new Window(44, 22, 35, 8);
                        windowsMap[contaID] = windowZona32;
                        windowZona32->operator<<(" " + to_string(contaID++) + "\n ");
                        // }
                } else if(arg1 == 3 && arg2 == 3){
                    //if(windowZona33 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona33 = new Window(80, 22, 35, 8);
                        windowsMap[contaID] = windowZona33;
                        windowZona33->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 3 && arg2 == 4){
                    // if(windowZona34 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona34 = new Window(116, 22, 35, 8);
                        windowsMap[contaID] = windowZona34;
                        windowZona34->operator<<(" " + to_string(contaID++) + "\n ");
                        //}
                } else if(arg1 == 4 && arg2 == 1) {
                    //if(windowZona41 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona41 = new Window(8, 30, 35, 8);
                        windowsMap[contaID] = windowZona41;
                        windowZona41->operator<<(" " + to_string(contaID++) + "\n ");
                    //}
                } else if(arg1 == 4 && arg2 == 2) {
                    //if(windowZona42 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona42 = new Window(44, 30, 35, 8);
                        windowsMap[contaID] = windowZona42;
                        windowZona42->operator<<(" " + to_string(contaID++) + "\n ");
                    //}
                } else if(arg1 == 4 && arg2 == 3) {
                    //if(windowZona43 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona43 = new Window(80, 30, 35, 8);
                        windowsMap[contaID] = windowZona43;
                        windowZona43->operator<<(" " + to_string(contaID++) + "\n ");
                    //}
                } else if(arg1 == 4 && arg2 == 4) {
                    //if(windowZona44 == nullptr){
                        buffer0 << "[CMD] Cria Zona: (" << arg1 << "x" << arg2 << ")" << endl;
                        windowZona44 = new Window(116, 30, 35, 8);
                        windowsMap[contaID] = windowZona44;
                        windowZona44->operator<<(" " + to_string(contaID++) + "\n ");
                    //}
                }
            }
        } else{
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "zrem" && count == 1){
        int arg1;
        while(str>>token){
            count++;
            if(count == 2){
                convert << token;
                if (convert >> num) {
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 2){
            habitacaoAtual->removeZona(arg1);
            buffer0 << "Remove Zona: " << arg1 << endl;
            windowsMap[arg1]->clear();
            auto it = windowsMap.find(arg1);
            if (it != windowsMap.end()) {
                delete it->second;
                windowsMap.erase(it);
            }
        } else{
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "zlista" && count == 1){
        while(str >> token) {
            count++;
            if(count == 2){
                buffer0 << "[ERRO] Argumento Invalid!" << endl;
            }
        }
        if(count == 1){
            buffer0 << "[CMD] Lista de Zonas: " << endl;
            buffer0 << habitacaoAtual->getAsString();
        } else {
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "zcomp" && count == 1){
        int arg1;
        while(str>>token){
            count++;
            if(count == 2){
                convert << token;
                if (convert >> num) {
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 2){
            buffer0 << "[CMD] Componentes da Zona: " << arg1 << endl;
            buffer0 << habitacaoAtual->listaComponentes(arg1);
        } else{
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "zprops" && count == 1){
        int arg1;
        while(str>>token){
            count++;
            if(count == 2){
                convert << token;
                if (convert >> num) {
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 2){
            buffer0 << "[CMD] Propriedades da Zona: " << arg1 << endl;
            buffer0 << habitacaoAtual->listaPropriedades(arg1);
        } else{
            buffer0 << "[ERRO] Argumentos Incorrect!" << endl;
        }
    } else if(token == "pmod" && count == 1){
        int arg1;
        float arg3;
        string arg2;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(validaString(token)){
                    arg2 = token;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(convert2 >> numF){
                    arg3 = numF;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Propriedade " << arg2 << "atualizada com " << arg3 << endl;
            habitacaoAtual->modificaValorPropriedade(arg1, arg2, arg3);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "cnovo" && count == 1){
        int arg1;
        string arg3;
        char arg2;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> ch){
                    arg2 = ch;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(validaString(token)){
                    arg3 = token;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Adiciona Componente!" << endl;
            habitacaoAtual->adicionaComponente(arg1, arg2, arg3);
            windowsMap[arg1]->operator<<(habitacaoAtual->colocaLetra(arg1, contaIDcomponente) + " ");
            contaIDcomponente++;
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "crem" && count == 1){
        int arg1, arg3;
        char arg2;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> ch){
                    arg2 = ch;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(convert2 >> num2){
                    arg3 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Remove Componente!" << endl;
            habitacaoAtual->removeComponente(arg1, arg2, arg3);
            windowsMap[arg1]->clear();
            windowsMap[arg1]->operator<<(" " + to_string(arg1) + "\n ");
            windowsMap[arg1]->operator<<(habitacaoAtual->colocaLetrasTodas(arg1));
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "rnova" && count == 1){
        int arg1, arg2, arg4;
        string arg3;
        float arg5, arg6;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid! 1" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> num2){
                    arg2 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid! 2" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(validaString(token)){
                    arg3 = token;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid! 3" << endl;
                    return buffer0.str();
                }
            } else if(count == 5){
                stringstream convert3;
                convert3 << token;
                if(convert3 >> num3){
                    arg4 = num3;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid! 4" << endl;
                    return buffer0.str();
                }
            } else if(count == 6){
                stringstream convert4;
                convert4 << token;
                if(convert4 >> numF){
                    arg5 = numF;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid! 5" << token << endl;
                    return buffer0.str();
                }
            } else if(count == 7){
                stringstream convert5;
                convert5 << token;
                if(convert5 >> numF){
                    arg6 = numF;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid! 6" << token << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 7){
            buffer0 << "[CMD] Adiciona Regra!" << endl;
            habitacaoAtual->criaRegra(arg1, arg2, arg3, arg4, arg5, arg6);
        } else if(count == 6){
            buffer0 << "[CMD] Adiciona Regra!" << endl;
            habitacaoAtual->criaRegra(arg1, arg2, arg3, arg4, arg5);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "pmuda" && count == 1){
        int arg1, arg2;
        string arg3;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> num2){
                    arg2 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(validaString(token)){
                    arg3 = token;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Muda Comando do Processador!" << endl;
            habitacaoAtual->mudaComandoProcessador(arg1, arg2, arg3);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "rlista" && count == 1){
        int arg1, arg2;
        while (str >> token) {
            count++;
            if (count == 2) {
                convert << token;
                if (convert >> num) {
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if (count == 3) {
                stringstream convert1;
                convert1 << token;
                if (convert1 >> num2) {
                    arg2 = num2;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 3){
            buffer0 << "[CMD] Lista de Regras!" << endl;
            buffer0 << habitacaoAtual->listaRegras(arg1, arg2);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "rrem" && count == 1){
        int arg1, arg2, arg3;
        while (str >> token) {
            count++;
            if (count == 2) {
                convert << token;
                if (convert >> num) {
                    arg1 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if (count == 3) {
                stringstream convert1;
                convert1 << token;
                if (convert1 >> num2) {
                    arg2 = num2;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if (count == 4) {
                stringstream convert2;
                convert2 << token;
                if (convert2 >> num) {
                    arg3 = num;
                } else {
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Removeu Regra!" << endl;
            habitacaoAtual->removeRegra(arg1, arg2, arg3);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "asoc" && count == 1){
        int arg1, arg2, arg3;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> num2){
                    arg2 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(convert2 >> num3){
                    arg3 = num3;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Associa Processador e Aparelho" << endl;
            habitacaoAtual->associaProcessadorAparelho(arg1, arg2, arg3);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "ades" && count == 1){
        int arg1, arg2, arg3;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> num2){
                    arg2 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(convert2 >> num3){
                    arg3 = num3;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Desassocia Processador e Aparelho" << endl;
            habitacaoAtual->desassociaProcessadorAparelho(arg1, arg2, arg3);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "acom" && count == 1){
        int arg1, arg2;
        string arg3;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> num2){
                    arg2 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(validaString(token)){
                    arg3 = token;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Envia Comando Manualmente" << endl;
            habitacaoAtual->enviaComandoManual(arg1, arg2, arg3);
            windowsMap[arg1]->clear();
            windowsMap[arg1]->operator<<(" " + to_string(arg1) + "\n ");
            windowsMap[arg1]->operator<<(habitacaoAtual->colocaLetrasTodas(arg1) + " ");
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "psalva" && count == 1){
        int arg1, arg2;
        string arg3;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(convert >> num){
                    arg1 = num;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 3){
                stringstream convert1;
                convert1 << token;
                if(convert1 >> num2){
                    arg2 = num2;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            } else if(count == 4){
                stringstream convert2;
                convert2 << token;
                if(validaString(token)){
                    arg3 = token;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 4){
            buffer0 << "[CMD] Salva Processador" << endl;
            habitacaoAtual->copiarProcessador(arg1, arg2, arg3);
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "prepoe" && count == 1){
        string arg1;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(validaString(token)){
                    arg1 = token;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
            if(count == 2){
                buffer0 << "[CMD] Repoe Copia Processador" << endl;
                habitacaoAtual->ativarCopiasProcessador(arg1);
                windowsMap[habitacaoAtual->retornaIDcopia(arg1)]->clear();
                windowsMap[habitacaoAtual->retornaIDcopia(arg1)]->operator<<(" " + to_string(habitacaoAtual->retornaIDcopia(arg1)) + "\n ");
                windowsMap[habitacaoAtual->retornaIDcopia(arg1)]->operator<<(habitacaoAtual->colocaLetrasTodas(habitacaoAtual->retornaIDcopia(arg1)));
            } else{
                buffer0 << "[ERRO] Argumento Incorrect!" << endl;
                return buffer0.str();
            }
        }
    } else if(token == "prem" && count == 1){
        string arg1;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(validaString(token)){
                    arg1 = token;
                } else{
                    buffer0 << "[ERRO] Argumento Invalid!" << endl;
                    return buffer0.str();
                }
            }
            if(count == 2){
                buffer0 << "[CMD] Remove Copia Processador" << endl;
                habitacaoAtual->apagaCopiaProcessador(arg1);
                habitacaoAtual->retornaIDcopia(arg1);

            } else{
                buffer0 << "[ERRO] Argumento Incorrect!" << endl;
                return buffer0.str();
            }
        }
    } else if(token == "plista" && count == 1){
        while(str >> token) {
            count++;
            if(count == 2){
                buffer0 << "[ERRO] Argumentos Incorret!" << endl;
            }
        }
        if(count == 1){
            buffer0 << "[CMD] Lista de Copias de Processador: " << this->iteration << endl;
            buffer0 << habitacaoAtual->listaCopiasProcessador();
        }
    } else if(token == "exec" && count == 1){
        string arg1;
        while (str >> token){
            count++;
            if(count == 2){
                convert << token;
                if(validaString(token)){
                    arg1 = token;
                } else{
                    buffer0 << "[ERRO] Argumento 1 Invalid!" << endl;
                    return buffer0.str();
                }
            }
        }
        if(count == 2){
            buffer0 << "[CMD] Carrega ficheiro de Texto" << endl;
            fstream file;
            arg1 += ".txt";

            file.open(arg1,ios::in);

            if(file.is_open()){
                string str1;
                while(getline(file,str1)){
                    validaComandos(str1);
                }
                file.close();
            }
        } else{
            buffer0 << "[ERRO] Argumento Incorrect!" << endl;
            return buffer0.str();
        }
    } else if(token == "clear" && count == 1){
        windowOutput->clear();
    } else{
        buffer0 << "[ERRO] Comando Inexistente!" << endl;
    }

    return buffer0.str();
}

void Simulador::avancaIteration(int n) {
    this->iteration += n;
    for (int i = 0; i < n; i++) {
        habitacaoAtual->avancaIteration();
    }
}

bool Simulador::validaString(const string& str) {
    bool temLetras = false;

    for (char c : str) {
        if (std::isalpha(c)) {
            temLetras = true;
        }
    }
    return temLetras;
}

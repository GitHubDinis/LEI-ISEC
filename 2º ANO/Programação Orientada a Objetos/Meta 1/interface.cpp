#include "interface.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "reserva.h"
#include "animais.h"
#include "alimentos.h"

using namespace std;

reserva r;
animal a(1,"ola","ola", 2,3,true,20,12,12,12,12,12);
alimentos o(10,10,10, false);

void interface::recebeComandos() {
    string cmd;
    int opcao;

    do {
        cout << "1 - Escrever comandos!\n2 - Ler comandos do ficheiro!" << endl;
        cin >> opcao;

        if(opcao == 1){
            cin.ignore();
            cout << "Introduza um comando: ";
            getline(cin, cmd);
            validaComandos(cmd);
        }else if(opcao == 2){
            leFicheiroComandos();
        }else{
            cout << "Introduza uma opcao valida!" << endl;
        }
    }while(opcao != 1 || opcao != 2);
}

int interface::validaComandos(string recebe) {

    stringstream str(recebe);
    stringstream convert;
    string token;
    int cont = 0;
    int num = 0;
    int aux;

    cout << endl;

    str >> token;
    cont++;
    // VALIDAÇÃO DO 1º ARGUMENTO
    if (token == "animal" && cont == 1) {
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                if ((token == "c" || token == "o" || token == "l" || token == "g" || token == "m")) {
                    cout << "Especie correta!" << endl;
                } else {
                    cout << "Especie incorreta!" << endl;
                }
            }
            // VALIDAÇÃO DO 3º ARGUMENTO
            if (cont == 3) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 4º ARGUMENTO
            } else if (cont == 4) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2 || aux == 4) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "kill" && cont == 1) {
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 3º ARGUMENTO
            } else if (cont == 3) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 3) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "killid" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "food" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                if ((token == "r" || token == "t" || token == "b" || token == "a")) {
                    cout << "Tipo correto!" << endl;
                } else {
                    cout << "Tipo incorreto!" << endl;
                }
            }
            // VALIDAÇÃO DO 3º ARGUMENTO
            if (cont == 3) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 4º ARGUMENTO
            } else if (cont == 4) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2 || aux == 4) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "feed" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 3º ARGUMENTO
            }else if (cont == 3) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 4º ARGUMENTO
            }else if (cont == 4) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 5º ARGUMENTO
            }else if (cont == 5) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 5) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "feedid" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
    }else if(token == "nofood" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 3º ARGUMENTO
            } else if (cont == 3) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2 || aux == 3) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "empty" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 3º ARGUMENTO
            } else if (cont == 3) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 3) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "see" && cont == 1) {
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 3º ARGUMENTO
            } else if (cont == 3) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 3) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "info" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "n" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
                // VALIDAÇÃO DO 3º ARGUMENTO
            } else if (cont == 3) {
                stringstream convert;
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 1 || aux == 2 || aux == 3) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "anim" && cont == 1){
        cout << "Comando valido!" << endl;
        //aux = cont;
        while(str >> token){
            cont++;
            cout << cont;
        }
        if (cont == 1){
            cout << "Numero de argumentos correto!" << endl;
            r.adicionaAnimais(a);
            r.adicionaAlimentos(o);
            cout << "\n" << r.getAsStringA();
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }

        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "visanim" && cont == 1){
        cout << "Comando valido!" << endl;
        //aux = cont;
        while(str >> token){
            cont++;
            cout << cont;
        }
        if (cont == 1){
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
    }else if(token == "store" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "restore" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "load" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 2) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "slide" && cont == 1){
        cout << "Comando valido!" << endl;
        while (str >> token) {
            cont++;
            // VALIDAÇÃO DO 2º ARGUMENTO
            if (cont == 2) {
                if ((token == "up" || token == "down" || token == "right" || token == "left")) {
                    cout << "Direcao correta!" << endl;
                } else {
                    cout << "Direcao incorreta!" << endl;
                }
            }
            // VALIDAÇÃO DO 3º ARGUMENTO
            if (cont == 3) {
                convert << token;
                if (convert >> num) {
                    cout << "Argumento " << cont << " valido!" << num << endl;
                } else {
                    cout << "Argumento " << cont << " invalido!" << num << endl;
                }
            }
            aux = cont;
        }
        if (aux == 3) {
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        // VALIDAÇÃO DO 1º ARGUMENTO
    }else if(token == "exit" && cont == 1){
        cout << "Comando valido!" << endl;
        //aux = cont;
        while(str >> token){
            cont++;
            cout << cont;
        }
        if (cont == 1){
            cout << "Numero de argumentos correto!" << endl;
        }else{
            cout << "Numero de argumentos incorreto!" << endl;
        }
        exit(1);
    }else{
        cout << "Comando Invalido!" << endl;
    }
    return 0;
}

int interface::leFicheiro() {

    ifstream input_file("constantes.txt");

    if(!input_file){
        cout << "Erro na leitura!" << endl;
        return -1;
    }

    string word, line;
    int i;

    while(!input_file.eof()) {
        getline(input_file, line);

        input_file >> word >> i;

        cout << "Parametro: " << word << " Valor: " << i << endl;
    }
    return 0;
}

int interface::leFicheiroComandos() {

    fstream file;

    file.open("comandos.txt", ios::in);

    if(file.is_open()){

        string str;

        while(getline(file, str)){
            validaComandos(str);
        }
        file.close();
    }
    return 0;
}

#include <cstdlib>
#include <iostream>
#include <sstream>

// AULA 5

using namespace std;


static int contador;



class automovel {
    int cilindrada;
    string cor;
    int id;
public:

    /*
        Construtor:

            - função que é chamada sempre que é criado um objeto de uma classe - faz a inicialização
            - tem o mesmo nome da classe
            - deve ser declarado como público
            - permite o overloading

    */

    automovel() {  // Construtor por omissão
        this->cilindrada = 1000; // this, ponteiro "hidden" que é passado a todos os membros não estáticos
        this->cor = "verde";
        id = ++contador;
        cout << "Construtor por omissao ..." << "Automovel " << id << endl;

        // o construtor não pode retornar nenhum valor
    }


    automovel(int cilind, string cor) { // construtor com parametros
        this->cilindrada = cilind;
        this->cor = cor;
        id = ++contador;
        cout << "Construtor com parametros ..." << "Automovel " << id << endl;
    }



    automovel(const automovel& obj) // Construtor por cópia
    {
        cilindrada = obj.cilindrada;
        cor = obj.cor;
        id = ++contador;
        cout << "Construtor por copia\n";

    }


    /*
       Destrutor: função que é chamada sempre que o ambito de duração do objeto de uma classe encerra-se - faz a "limpeza"
       -  Não podem ser chamados explicitamente pelo programador.
   */

    ~automovel() { // destrutor
        // não tem argumentos, e permite fazer a "limpeza"
        contador--;
        cout << "A destruir automovel " << id << endl;
    }

    string getAsString() const {
        ostringstream bufferO;
        bufferO << "Cilindrada: " << cilindrada << " -> " << "Cor: " << cor << "\n";
        return bufferO.str();
    }


    // GETTERS e SETTERS

};



int main() {

    automovel a; // construtor por omissao

    cout << "O Automovel A->" << a.getAsString();


    automovel b(1200, "Amarelo");

    cout << "O Automovel B->" <<  b.getAsString();


    automovel c(a);

    cout << "O Automovel C->" << c.getAsString();



    return 0;
}

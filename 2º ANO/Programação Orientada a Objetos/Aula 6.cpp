#include <iostream>
#include <sstream>

// AULA 6

using namespace std;

class msg{
    int numero;
    char letra;
    static int count;

public:
    msg(char letra = 'x'){
        this->letra = letra;
        numero = count++;
        cout << "Criado: " << getAsString();
    }

    msg(const msg& c){
        this->letra = toupper(c.letra);
        this->numero = -c.numero;
        cout << "Contruindo por copia: " << getAsString();
    }

    ~msg(){
        count--;
        cout << "Terminado: " << getAsString();
    }

    string getAsString() const{
        ostringstream buffer0;
        buffer0 << "Letra: " << letra << " Numero: " << numero << endl;
        return buffer0.str();
    }
};

int msg::count = 1;

int main() {

    msg a('a'), b;     // Alínea A
    cin.get();

    msg& c = b;             // Alínea B
    cin.get();

    msg d = b;              // Alínea C
    cin.get();

    a = b;                  // Alínea D
    cin.get();

    msg matriz[2] = {'a','b'};   // Alínea E
    for (msg x : matriz) {
        cout << x.getAsString() << endl;
    }
    cin.get();



    cout << "Pressione ENTER para continuar...";
    cin.get();

    return 0;
}

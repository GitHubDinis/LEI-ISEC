#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <initializer_list>
//#include <span>

using namespace std;

// EXERCICÍO 1 (FICHA 3)
// ALÍNEA A)

class Tabela{
    static const int armazenamento = 10;
    int numeros[armazenamento];
public:
    void preenche(){
        for (int i = 0; i < armazenamento; i++) {
            numeros[i] = 3;
        }
    }

    void altera(int pos){
        if(pos < armazenamento){
            numeros[pos] = 7;
        } else{
            cout << "Pos inexistente!" << endl;
            return;
        }
    }

    void show(){
        for (int i = 0; i < armazenamento; ++i) {
            cout << numeros[i] << " ";
        }
    }

    // ALÍNEA B)
    /*span <int> getInitializer(){
        span <int> list {numeros, static_cast<size_t> armazenamento}
        return list;
    }*/

    // ALÍNEA C)
    Tabela(){
        for (int i = 0; i < armazenamento; i++) {
            numeros[i] = 10;
        }

        cout << "Construido!" << endl;
    }

    Tabela(int valor){
        for (int i = 0; i < armazenamento; i++) {
            numeros[i] = valor;
        }

        cout << "Construido!" << endl;
    }

    Tabela(int a, int b){
        numeros[0] = a;
        for (int i = 1; i < armazenamento; i++) {
            numeros[i] = a + b*i;
        }

        cout << "Construido!" << endl;
    }

    Tabela(initializer_list<int> list){
        int i = 0;
        for(int j : list){
            if(i < armazenamento){
                numeros[i++] = j;
            }
        }
        for (int j = i; j < armazenamento; j++) {
            numeros[j] = 11;
        }

        cout << "Construido!" << endl;
    }

    // ALÍNEA E)
    void verficiaNumero(int numero){
        for (int i = 0; i < armazenamento; i++) {
            if(numero == numeros[i]){
                cout << "Numero Existente!" << endl;
            }
        }
    }

    // ALÍNEA F)
    void verificaObjetos(Tabela t1, Tabela t2){
        static int iguais = 0;

        for (int i = 0; i < t1.armazenamento; ++i) {
            for (int j = 0; j < t2.armazenamento; ++j) {
                if(t1.numeros[i] == t2.numeros[j]){
                    iguais++;
                }
            }
        }

        if(iguais == t1.armazenamento && iguais == t2.armazenamento){
            cout << "Tem os mesmos numeros!" << endl;
        } else{
            cout << "Nao tem os mesmos numeros!" << endl;
        }
    }

    // ALÍNEA G)
    ~Tabela(){
        cout << "Destruido!" << endl;
    }

};

void Recebe(Tabela t){

}

Tabela Devolve(Tabela t){
    return t;
}

void Inicializa(){
    Tabela t1;
    t1.preenche();
    Tabela t2 = t1;
}

// EXERCICÍO 2 (FICHA 3)
// ALÍNEA A)

class Automovel{
    string matricula;
    string marca;
    string combustivel;
    int modelo;
    bool emMovimento;
public:
    Automovel(string mat, string mar, string com, int mod, bool m){
        this->matricula = mat;
        this->marca = mar;
        this->combustivel = com;
        this->modelo = mod;
        this->emMovimento = m;
    }

    void mover(){
        emMovimento = true;
    }
    void parar(){
        emMovimento = false;
    }

    string getAsString() const{
        ostringstream os;
        os << "\nMatricula: " << matricula << "\nMarca: " << marca << "\nCombustivel: " << combustivel << "\nModelo: " << modelo << endl;
        return os.str();
    }
};

int main() {

    /*// EXERCICÍO 1 (FICHA 3)
    // ALÍNEA A)
    Tabela t1;
    t1.preenche();
    t1.show();
    t1.altera(3);
    putchar('\n');
    t1.show();
    putchar('\n');

    // ALÍNEA B)
    *//*for (int i : t1.getInitializer()) {
        cout << i << "\t";
    }*//*

    // ALÍNEA C)
    Tabela t2;
    t2.show();
    putchar('\n');
    Tabela t3(15);
    t3.show();
    putchar('\n');
    Tabela t4(4, 7);
    t4.show();
    putchar('\n');
    Tabela t5({10, 33, 55, 20, 32});
    t5.show();
    putchar('\n');

    // ALÍNEA E)
    t4.verficiaNumero(11);
    putchar('\n');
    // ALÍENA F)
    //t1.verificaObjetos(t1, t1);

    // ALÍNEA G)
    Recebe(t3);
    Devolve(t1);
    Inicializa();*/

    // EXERCICÍO 2 (FICHA 3)

    Automovel a1("AX18VX", "Peugeot", "Gasolina", 208, false);

    cout << "Carro 1:" << a1.getAsString() << endl;

    return 0;
}
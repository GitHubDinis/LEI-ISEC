#include <iostream>

using namespace std;

// AULA 2 (28/09/2023)

// EXERCICÍO 2
void imprime(string s1){
    cout << s1 << endl;
}

void imprime(string s1, int num){
    cout << s1 << ": " << num << endl;
}

void imprime(int num, string s1){
    cout << num << " " << s1 << endl;
}

// EXERCICÍO 3 (ALÍNEA A)
/*int multiplica(){
    return 1;
}

int multiplica(int num){
    return num;
}

int multiplica(int num1, int num2){
    return num1 * num2;
}

int multiplica(int num1, int num2, int num3){
    return num1 * num2 * num3;
}*/

// EXERCICÍO 3 (ALÍNEA B)
int multiplica(int num1 = 1, int num2 = 1, int num3 = 1){
    return num1 * num2 * num3;
}

// EXERCICÍO 1 (ALÍNEA A)
namespace DataStore{
    bool dadosSaoValidos(string frase){
        if(frase.length() < 10 && frase.length() > 5){
            return true;
        } else{
            return false;
        }
    }
}

namespace UserInterface{
    bool dadosSaoValidos(string frase){
        if(frase[1] >= 'A' && frase[1] <= 'Z'){
            return true;
        } else{
            return false;
        }
    }
}

using namespace DataStore;

// EXERCICÍO 4

void troca(int &num1, int &num2){
    int aux = num1;
    num1 = num2;
    num2 = aux;
}

void trocaP(int *num1, int *num2){
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}

int seleciona(int &num1, int &num2, char seleciona){
    try{
        if(seleciona == 'm'){
            if(num1 < num2){
                return num1;
            } else if(num2 < num1){
                return num2;
            }
        } else if(seleciona == 'M'){
            if(num1 > num2){
                return num1;
            } else if(num2 > num1){
                return num2;
            }
        } else if(seleciona == 'p'){
            return num1;
        } else if(seleciona == 'u'){
            return num2;
        } else{
            throw seleciona;
        }
    } catch (char caracter){
        cout << "Codigo desconhecido!" << endl;
    }
    return 0;
}

// EXERCICÍO 6 (ALÍNEA A)
struct Tabela{
    int tam;
    int matriz[];
};

Tabela preencheTabela(Tabela a){
    cout << "Preencher quantos?";
    cin >> a.tam;

    for (int i = 0; i < a.tam; i++) {
        cout << "Preencher:";
        cin >> a.matriz[i];
    }

    return a;
}

void listaConteudo(Tabela a){
    for (int i = 0; i < a.tam; i++) {
        cout << "Valor " << i << ": " << a.matriz[i] << endl;
    }
}

// EXERCICÍO 6 (ALÍNEA B)

void mostraValor(Tabela a, int pos){
    cout << "Valor: " << a.matriz[pos - 1] << endl;
}

Tabela alteraValor(Tabela a, int pos, int novo){

    a.matriz[pos - 1] = novo;

    return a;
}

// MAIN

int main() {
    cout << "Hello, Aula 2!" << endl;

    // EXERCICÍO 2
    //imprime("Programacao Orientada a Objetos");
    //imprime("Horas por aula teorica", 2);
    //imprime(3, "horas em cada aula pratica!");

    // EXERCICÍO 3 (ALÍNEA A E ALÍNEA B)
    //cout << "\n" << multiplica() << "\n" << multiplica(5);
    //cout << endl << multiplica(2,3) << endl << multiplica(2,3,4);

    // EXERCICÍO 1 (ALÍNEA B)
    // i)
    //DataStore::dadosSaoValidos("O Dinis tem 20 anos");
    //UserInterface::dadosSaoValidos("O Dinis tem 20 anos");
    // ii)
    //using UserInterface::dadosSaoValidos("O Dinis tem 20 anos");
    //using DataStore::dadosSaoValidos("O Dinis tem 20 anos");
    // iii)
    //dadosSaoValidos("O Dinis tem 20 anos");
    // iv)
    // Assim não funciona.

    // EXERCICÍO 4
    //int a = 5, b = 10;
    //troca(a, b);
    //trocaP(&a, &b);
    //cout << "\na = " << a << "\nb = " << b;

    // EXERCICÍO 5
    //int c = seleciona(a, b, 'm');
    //cout << endl << "Valor: " << c << endl;

    // EXERCICÍO 6
    Tabela tab;
    tab = preencheTabela(tab);
    listaConteudo(tab);
    mostraValor(tab, 3);
    alteraValor(tab, 3, 5);
    listaConteudo(tab);

    return 0;
}

#include <iostream>

// AULA 1

// EXERCICÍO 1

//using namespace std;

//int main() {
//    cout << "Hello, World!" << std::endl;
//    return 0;
//}

//EXERCICÍO 2

#define N 50

//using namespace std;

//int main(){

//    char nome[N];
//    int idade;

//    cout << "Escreva o nome: ";
//    cin >> nome;
//    cout << endl;

//    cout << "Escreva a idade: ";
//    cin >> idade;
//    cout << endl;

//    cout << "Nome: " << nome << "\nIdade: " << idade << endl;

//    return 0;
//};

//EXERCICÍO 3

//using namespace std;

//int main(){

//    string nome;
//    int idade;

//    cout << "Escreva o nome: ";
//    getline(cin, nome);
//    cout << endl;

//    cout << "Escreva a idade: ";
//    cin >> idade;
//    cout << endl;

//    cout << "Nome: " << nome << "\nIdade: " << idade << endl;

//    return 0;
//};


// EXERCICÍO 4

using namespace std;

void imprime(string a){
    cout << a << endl;
};

void imprime(string a, int b){
    cout << a << b << endl;
};

void imprime(int a, string b){
    cout << a << b << endl;
};

int main(int argc, const char * argv[]){
    imprime("ola");
    imprime("a idade e: ", 25);
    imprime(100, " Euros");

    return 0;
};
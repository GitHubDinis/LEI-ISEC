#include <sstream>
#include <iostream>
#include <algorithm>

// AULA 2

//using namespace std;

//int main() {

//    int a;

//    cout << "Digite um numero inteiro:\n";
//    cin >> a;

//    while (1) {
//        if (cin.fail()) {
//            cin.clear();
//            cout << "Digitou um numero errado :)" << endl;
//            cin >> a;
//        }
//        if(!cin.fail()){
//            break;
//        }
//    }

//    cout << "O numero e: " << a << endl;
//    return 0;
//}

// EXERCICÍO 5

//using namespace std;

//int soma(){
//    return 0;
//}

//int soma(int a){
//    return a;
//}

//int soma(int a, int b){
//    return a + b;
//}

//int soma(int a, int b, int c){
//    return a + b + c;
//}

//int main(int argc, char **argv, char **envp){
//    cout << "\n" << soma() << endl << soma(1);
//    cout << "\n" << soma(1,2) << endl << soma(1,2,3);

//    return 0;
//}

// EXERCICÍO 6

//using namespace std;

//int troca(int *a, int *b){
//    int c;

//    c = *a;
//    *a = *b;
//    *b = c;

//    return 0;
//}

//int main(){
//    int a = 5, b = 10;
//    troca(&a,&b);
//    cout << "\na = " << a << "\nb = " << b;
//}

// EXERCICÍO 7

//using namespace std;

//void verifica(){
//    istringstream s2("Pedro Jose Silva");
//    string palavra, aux;

//    while(s2 >> palavra){
//        cout << palavra << endl;

//        if(palavra == "Silva")
//            aux = palavra;
//    }

//    if(aux == "Silva")
//        cout << "Conheco este nome!" << endl;

//    cout << "Guardado em s2: " << s2.str() << endl;

//    s2.str("Novo texto!"); //outro valor guardado em s2
//    cout << "Guardado em s2: " << s2.str() << endl;
//}

//int main(){
//    verifica();
//}

// OUTRO EXERCICÍO

//using namespace std;

//int main(){
//    istringstream s1("man -n l");
//    string comand, aux;

//    while(s1 >> comand) {
//        cout << comand << endl;
//    }

//    cout << "Digitou o comando " << s1.str() << " e as flags " << s1.str() << endl;
//}

// EXERCICÍO 8

using namespace std;

int main(){

    cout << "Escreva o seu nome completo: " << endl;

    string palavra, aux, s;

    getline(cin, s);

    istringstream s3(s);

    while(s3 >> palavra){
        aux = palavra;

        reverse(palavra.begin(), palavra.end());

        if(aux == "fim")
            return 0;

        cout << "Nome invertido: " << palavra << " " << endl;

        if(aux == palavra)
            cout << " Palindromo Identificado!" << endl;

        cout << "Carregue ENTER para prosseguir";

        if(cin.get() == '\n');
    }
}
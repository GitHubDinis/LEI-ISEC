#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {

    //char nome[20];
    string nome;
    int idade = 0;

    // EXERCICÍO 2 (ALÍNEA A)

    /*printf("Nome do Utilizador:");
    scanf("%s", nome);
    printf("Idade do Utilizador:");
    scanf("%d", &idade);

    printf("O utilizador %s tem %d anos!", nome, idade);*/

    // EXERCICÍO 2 (ALÍNEA B E ALÍNEA C E ALÍNEA D)

    /*cout << "Nome do utilizador:";
    //cin >> nome;
    getline(cin, nome);

    while(idade <= 0) {
        cout << "Idade do utilizador:";
        cin >> idade;
    }

    cout << "O utilizador " << nome << " tem " << idade << endl;*/

    // EXERCICÍO 2 (ALÍNEA E)

    /*int numeroCaracteres;

    numeroCaracteres = nome.length();
    cout << "Numero de caracteres do nome: " << numeroCaracteres << endl;

    for (int i = 0; i < nome.length(); i++) {
        cout << nome[i] << endl;
    }

    for (char letra : nome){
        cout << letra << endl;
    }*/

    // EXERCICÍO 3 (ALÍNEAS A E B)

    string palavra;

    cout << "Nome:";
    getline(cin,nome);

    istringstream buffer(nome);

    while(buffer >> palavra){
        cout << palavra << endl;

        if(palavra == "Fernando"){
            cout << "O programa conhece o Fernando!" << endl;
        }
    }

    // EXERCICÍO 4

    /*string word, palindromo, temp;

    while(cout << "Palavra:") {

        cin >> word;

        for (int i = word.length() - 1; i >= 0; i--) {
            cout << word[i];
        }
        cout << endl;

        temp = word;
        reverse(temp.begin(), temp.end());

        if (word == temp) {
            cout << "\t" << word << " -> palindromo" << endl;
        } else if (word == "fim") {
            return 0;
        }

        system("pause");
    }*/

    // EXERCICÍO 5

    /*string decimal[10] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};
    string dec;
    int num;

    do{
        cout << "Introduza um numero:";
        getline(cin,dec);

        string out;
        for(int i = 0; i < 10; i++){
            string index = to_string(i + 1);
            if(dec == decimal[i])
                out = index;    //escrever numerico no output, recebendo extenso
            if(dec == index){
                out = decimal[i];   //escrever extenso, recebendo numerico
            }
        }
        cout << out;

        if(dec == "fim"){
            return 0;
        }

        //system("pause");
    }while(num < 1 || num > 9);*/

    // EXERCICÍO 6

    /*string decimal[10] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};
    string fich, mytext;
    ifstream myfile("file.txt");

    // IMPRIMIR FICHEIRO DE TEXTO INICIAL.
    *//*if(myfile.is_open()) {
        while(!myfile.eof()){
            getline(myfile, mytext);
            cout << mytext << endl;
        }
    }else{
        cout << "Couldn't open file" << endl;
    }*//*

    do{
        cout << "Introduza o nome do ficheiro:";    //fazer verificacao do nome do ficheiro
        getline(cin,fich);

        while(!myfile.eof()){
            string line, out;

            getline(myfile, line);

            for(int i = 0; i < 10; i++){
                string index = to_string(i+1);
                if(line == decimal[i])
                    out = index;    //poe numerico no output, pega extenso do ficheiro
                if(line == index){
                    out = decimal[i];   //escrever extenso, pega numerico do ficheiro
                }
            }
            cout << out << endl;
        }

        if(fich == "fim"){
            return 0;
        }

        //system("pause");
    }while(fich != "file.txt");

    myfile.close();*/

    // EXERCICÍO 7

    /*int inteiro;
    string extenso;
    string decimal[10] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez"};

    while (true) {
        cout << "Extenso Inteiro (ou 'fim' para sair):";
        cin >> extenso;

        if (extenso == "fim") {
            break;
        }

        cout << "Digite o number:";
        cin >> inteiro;

        string out;

        for (int i = 0; i < 10; i++) {
            if (extenso == decimal[i]) {
                out = to_string(i + 1); // Converter o índice em número
                break; // Se encontrado, não é necessário continuar o loop
            }
        }

        if (inteiro == stoi(out)) {
            cout << "Certo!" << endl;
        } else {
            cout << "Errado!" << endl;
        }
    }*/

    return 0;
}

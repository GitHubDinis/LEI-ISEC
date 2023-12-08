#include <iostream>

#include "MyString.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    MyString m1("MyString de Teste");
    MyString m2("Outra");
    MyString m3(m2);

    cout << "Fim" << endl;
    m2 = m1;
    cout << "Tamanho: " << m1.getTam() << endl;
    cout << "Caracter: " << m1.at(0) << endl;
    m1.concat(m1);
    cout << m1.getMyString() << endl;
    m1.clear();
    cout << m1.getTam() << endl;
    cout << "Fim!" << endl;

    return 0;
}
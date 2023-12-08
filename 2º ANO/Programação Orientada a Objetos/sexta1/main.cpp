#include <iostream>

#include "Vetor.h"

using namespace std;

// EXERCÍCIO 2 (FICHA 5)

int main() {
    cout << "Hello, World!" << endl;

    // ALÍNEA B)

    /*Vetor v1(2.0, 1.0), v2(1.0, 3.0), v3(2.2), z;
    z = v1 + v2 + v3;
    cout << v1 << "+" << v2 << "+" << v3 << "=" << z << endl; // obs: "(x,y)"
    z = v1 + 10.0;
    cout << v1 << " + " << " 10 = " << z << endl;
    //z = 20.0 + v1;
    cout << "20 + " << v1 << " = " << z << endl;
    z = v1 - v2;
    cout << v1 << " - " << v2 << " = " << z << endl;
    Vetor a(1.0, 1.0), b(2.0, 4.0);
    cout << " a= " << a << " b= " << b << endl;
    a += b += v1;
    a += b;
    a += 10.0;
    cout << " a= " << a << endl;
    cout << "(a == b)? " << (a == b) << endl;
    cout << "(a != b)? " << (a != b) << endl;*/

    // ALÍNEA D)

    Vetor a(1,1);
    double modulo = double(a); // significado = modulo do vetor
    double k = a;
    Vetor b = 2.5; // verifique primeiro se já está a ser possível isto
    //b = a + 4.0; // verifique se fizer um operador para este caso dará erro
    Vetor c(1.0, 1.0);
    cout << "Operadores unarios";
    cout <<"\nc=" << c;
    cout << "\n++ -> c=" << ++c;
    cout <<"\nc="<< c;
    Vetor d(1.0, 1.0);
    cout <<"\nd="<< d ;
    cout << "\nd++:" << d++;
    cout << "\nd=" << d << endl;
    cin >> a >> b;
    cout << a << "\n" << b;
    if ((bool) a)
        cout << "o vetor a tem as coordenadas 0,0";

    return 0;
}

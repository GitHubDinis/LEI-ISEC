#include <iostream>

#include "Fracao.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Fracao a(1,2), b(3);
    const Fracao c(3,4);
    a = b*c;
    Fracao e = a*b*c;
    a = b*4;
    a = 4*b;
    cout << a;
    cout << b << c;
    a * b;
    a.setNum(1);
    a.setDen(2);
    b.setNum(1);
    b.setDen(3);
    (a*=b)*=c;
    cout << a;
    cout << a++;
    cout << ++a;
    cout << a;
    //int valor = a;
    //if(a == b)
    //    cout << "Sao iguais!\n";
    //if(a != b)
    //    cout << "Sao diferentes!\n";
    //cin >> a >> b;

    return 0;
}

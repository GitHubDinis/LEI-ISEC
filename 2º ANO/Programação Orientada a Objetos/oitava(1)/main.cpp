#include <iostream>
#include <cstring>

#include "MyString.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    MyString m1("MyString de Teste");
    MyString m2("Outra");
    MyString m3 = m2;
    m2 = m1;
    cout << m1.getTam();
    //cout << m1.at(0);
    //m1.concat(m1);
    //cout << m1.getMyString();
    //m1.clear()

    return 0;
}

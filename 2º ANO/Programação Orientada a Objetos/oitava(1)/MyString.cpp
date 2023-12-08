#include "MyString.h"

MyString::MyString() {
    p = nullptr;
    tam = 0;
    cout << "CONSTR. de MyString!" << endl;
}

MyString::MyString(char *p) {
    this->p = new char[strlen(p) + 1];
    strcpy(this->p, p);
    tam = strlen(p) + 1;
    cout << "CONSTR. de MyString!" << endl;
}

MyString::~MyString() {
    cout << "DESTR. de MyString!" << p << endl;
    delete[] p;
}

int MyString::getTam() const {
    return tam;
}

void MyString::getMyString() {
    for (int i = 0; i < tam; i++) {
        printf("%c", p[i]);
    }
}





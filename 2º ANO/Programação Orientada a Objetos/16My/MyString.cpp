#include "MyString.h"

MyString::MyString() {
    p = nullptr;
    tam = 0;
    cout << "CONSTR. de MyString!" << endl;
}

MyString::MyString(const char *p) {
    this->p = new char[strlen(p) + 1];
    strcpy(this->p, p);
    tam = strlen(p) + 1;
    cout << "CONSTR. de MyString!" << endl;
}

MyString::MyString(MyString &outro) {
    p = nullptr;
    *this = outro;
    cout << "CONSTR. por copy!" << endl;
}

MyString::~MyString() {
    cout << "DESTR. de MyString!" << p << endl;
    delete[] p;
}

int MyString::getTam() const {
    return tam;
}

char MyString::getMyString() {
    return *this->p;
}

char MyString::at(int pos) {
    for (int i = 0; i < tam; ++i) {
        if(i == pos){
            return p[i];
        }
    }
    return 0;
}

void MyString::concat(MyString string1) {
    char *novoP = new char[tam + string1.tam + 1]; // reservar novo maior
    strcpy(novoP, p); // copiar antigo para inicio do novo
    delete[] p;
    p = novoP;
    strcat(this->p, string1.p);
    tam += string1.tam;
}

MyString& MyString::operator=(const MyString &o) {
    if(this != &o) {
        delete[] p;
        p = new char[o.tam + 1];
        tam = o.tam;
        strcpy(p, o.p);
    }
    return *this;
}

void MyString::clear() {
    this->tam = 0;
}


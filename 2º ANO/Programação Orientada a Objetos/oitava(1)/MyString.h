#ifndef OITAVA_1__MYSTRING_H
#define OITAVA_1__MYSTRING_H

#include <iostream>
#include <string.h>

using namespace std;

class MyString {
public:
    MyString();
    MyString(char * p);
    ~MyString();

    int getTam() const;
    void getMyString();
private:
    int tam;
    char *p;
};


#endif //OITAVA_1__MYSTRING_H

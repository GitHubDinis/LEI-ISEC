#ifndef INC_16MY_MYSTRING_H
#define INC_16MY_MYSTRING_H

#include <iostream>
#include <cstring>

using namespace std;

class MyString {
public:
    MyString();
    MyString(const char *p);
    MyString(MyString & outro);
    ~MyString();

    int getTam() const;
    char getMyString();
    char at(int pos);
    void concat(MyString string1);
    void clear();

    MyString& operator=(const MyString &o);
private:
    int tam;
    char *p;
};

#endif //INC_16MY_MYSTRING_H

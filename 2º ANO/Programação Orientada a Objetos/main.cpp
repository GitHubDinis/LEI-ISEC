#include <iostream>
#include <string>

// AULA 3

// EXERCICÍO 9

using namespace std;

//int IntToString(int *x){

//    if (*x = 1){
//        cout << "Corresponde a UM" << endl;
//   } else if (*x = 2){
//        cout << "Corresponde a DOIS" << endl;
//    }

//    return 0;
//}

int main(int argc, char ** argv) {
    int num;
    string str;

    cout << "Escreva o inteiro: " << endl;
    cin >> num;

    str = to_string(num);

    cout << "Corresponde a: " << str << endl;

    return 0;
}

// EXERCICÍO 11

//using namespace std;

//first namespace
//namespace DataStore {
//    void Dummyfunc(){
//        cout << "Inside DataStore (dummy)" << endl;
//    }
//}

//second namespace
//namespace UserInterface {
//    void Dummyfuc(){
//        cout << "Inside DataStore (dummy)" << endl;
//    }
//}

//declare with using
//using UserInterface::Dummyfuc;

//using DataStore::Dummyfunc;

//int main(){
    //Sem usar a declaracao using namespace
//    DataStore::Dummyfunc();
//    UserInterface::Dummyfuc();

    //Usando using mas nao using namespace...
    //Dummyfunc();

//    return 1;
//}



#include <iostream>
#include <string>

// AULA 3

// EXERCICÍO 9

using namespace std;

int main(int argc, char ** argv) {

    cout << "Write an integer: ";
    int num;

    cin >> num;

    if (num > 10){
        cout << "Error: Number must be less than or equal to 10" << endl;
        return 0;
    }

    string array[] {"zero", "one", "two", "three", "four", "five","six", "seven", "eight", "nine", "ten"};

    cout << num << " stands for: "<< array[num];

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



#ifndef WORK_INTERFACE_H
#define WORK_INTERFACE_H

#include <string>

using namespace std;

class interface{

public:
    static void recebeComandos();
    static int validaComandos(string recebe);
    static int leFicheiro();
    static int leFicheiroComandos();
};

#endif //WORK_INTERFACE_H

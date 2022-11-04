#include <iostream>
#include "Televisao.h"

// AULA 7
// EXERCICÍO 9 (Ficha 2)

using namespace std;

int main() {

    Televisao TV({"rtp1", "rtp2", "sic", "tvi", "panda", "playboy"});
    TV.LigarTV();
    TV.DiminuirVolume();

    return 0;
}

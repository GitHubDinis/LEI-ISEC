#include "retangulo.h"
#include <sstream>

using std::ostringstream;

retangulo::retangulo(const ponto &p, double alt, double lar) : cse(p.getX(), p.getY()), altura(alt), largura(lar) {

}

retangulo::retangulo(const retangulo &r) : retangulo(r.cse, r.altura, r.largura) {

}

retangulo::~retangulo() {
    std::cout << " a destruir: " << getAsString() << "\n";
}

string retangulo::getAsString() const {
    ostringstream os;
    os << "retangulo com canto superior esquerdo em " << cse.getAsString();
    os << " altura " << altura << " largura " << largura;
    return os.str();
}

double retangulo::area() const { return altura * largura; }

void retangulo::setCanto(const ponto &nc) {
    cse = nc;
}

#include "Vetor.h"

Vetor::Vetor(double x, double y): x(x), y(y){
    if(x == 0){
        x = y;
    } else if(y == 0){
        y = x;
    }
    cout << "Construtor de Vetor!" << endl;
}

Vetor::~Vetor() {
    cout << "Destrutor de Vetor!" << endl;
}

double Vetor::getX() const {
    return x;
}

double Vetor::getY() const {
    return y;
}

void Vetor::setX(double x) {
    this->x = x;
}

void Vetor::setY(double y) {
    this->y = y;
}

string Vetor::getAsString() const {
    ostringstream buffer0;
    buffer0 << "Coordenadas: " << x << ", " << y << endl;
    return buffer0.str();
}

Vetor &Vetor::operator+(const Vetor &v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vetor &Vetor::operator-(const Vetor &v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vetor &Vetor::operator+=(const Vetor &v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

bool Vetor::operator==(const Vetor &v) {
    if(this->x == v.x && this->y == v.y)
        return true;
    return false;
}

bool Vetor::operator!=(const Vetor &v) {
    if(this->x != v.x && this->y != v.y)
        return true;
    return false;
}

Vetor::operator double() const {
    double comprimento = 0;
    comprimento = sqrt(this->x*this->x + this->y*this->y);
    return comprimento;
}

Vetor &Vetor::operator++() {
    this->x++;
    this->y++;
    return *this;
}

Vetor Vetor::operator++(int) {
    Vetor anterior(this->x, this->y);
    this->x++;
    this->y++;
    return anterior;
}

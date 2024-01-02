#include "Zona.h"

static int id = 1;

Zona::Zona(int linha, int coluna) : linha(linha), coluna(coluna) {
    ID = id++;
    this->adicionarPropriedades();
    cout << "Construtor de Zona!" << endl;
}

Zona::~Zona() {
    for(auto propriedade : propriedades)
        delete propriedade;
    propriedades.clear();
    for(auto aparelho : aparelhos)
        delete aparelho;
    aparelhos.clear();
    for(auto processador : processadores)
        delete processador;
    processadores.clear();
    for(auto sensor : sensores)
        delete sensor;
    sensores.clear();

    cout << "Destrutor de Zona!" << endl;
}

int Zona::getLinha() const {
    return this->linha;
}

int Zona::getColuna() const {
    return this->coluna;
}

int Zona::getID() const {
    return this->ID;
}

string Zona::listaComponentes() const {
    ostringstream buffer0;

    auto it = sensores.begin();
    while(it < sensores.end()){
        buffer0 << (*it)->getAsString();
        it++;
    }
    auto itA = aparelhos.begin();
    while(itA < aparelhos.end()){
        buffer0 << (*itA)->getAsString();
        itA++;
    }
    auto itP = processadores.begin();
    while(itP < processadores.end()){
        buffer0 << (*itP)->getAsString();
        itP++;
    }

    return buffer0.str();
}

string Zona::listaPropriedades() const {
    ostringstream buffer0;
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        buffer0 << (*it)->getAsString() << endl;
        it++;
    }
    return buffer0.str();
}

bool Zona::modificaPropriedade(string nome, float valor) {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if((*it)->getNome() == nome){
            (*it)->setValor(valor);
            return true;
        }
        it++;
    }
    return false;
}

bool Zona::removeComponente(char letra, int IDcomponente) {
    if (letra == 'a') {
        auto itA = aparelhos.begin();
        while (itA < aparelhos.end()) {
            if ((*itA)->getIDnum() == IDcomponente) {
                aparelhos.erase(itA); // USAR QUAL?
                delete *itA;
                return true;
            }
            itA++;
        }
    } else if(letra == 's') {
        auto itS = sensores.begin();
        while (itS < sensores.end()) {
            auto itR = regras.begin();
            while(itR < regras.end()){
                if((*itR)->getNomeSensor() == (*itS)->getTipoOuComando()){
                    return false;
                }
                itR++;
            }
            if ((*itS)->getIDnum() == IDcomponente) {
                sensores.erase(itS);
                delete *itS;
                return true;
            }
            itS++;
        }
    } else if(letra == 'p') {
        auto itP = processadores.begin();
        while (itP < processadores.end()) {
            if ((*itP)->getIDnum() == IDcomponente) {
                processadores.erase(itP); // USAR QUAL?
                //delete *itP;
                return true;
            }
            itP++;
        }
    }
    return false;
}

string Zona::getAsString() {
    this->contaComponentes();
    ostringstream buffer0;
    buffer0 << "ID: " << this->ID << ", Sensores: " << this->nSensores << ", Processadores: " << this->nProcessadores << ", Aparelhos: " << this->nAparelhos;
    return buffer0.str();
}

bool Zona::adicionaComponente(char letra, string tipoOuComando) {
    if(letra == 's'){
        Sensor *novoSensor = new Sensor(retornaPropriedade(tipoOuComando));
        sensores.push_back(novoSensor);
        return true;
    } else if(letra == 'p'){
        Processador *novoComponente = new Processador(tipoOuComando);
        processadores.push_back(novoComponente);
        return true;
    } else if(letra == 'a'){
        if(tipoOuComando == "aquecedor"){
            Aparelho *novoComponente = new Aquecedor(this->propriedades);
            aparelhos.push_back(novoComponente);
        } else if(tipoOuComando == "aspersor"){
            Aparelho *novoComponente = new Aspersor(this->propriedades);
            aparelhos.push_back(novoComponente);
        } else if(tipoOuComando == "lampada"){
            Aparelho *novoComponente = new Lampada(this->propriedades);
            aparelhos.push_back(novoComponente);
        } else if(tipoOuComando == "refrigerador"){
            Aparelho *novoComponente = new Refrigerador(this->propriedades);
            aparelhos.push_back(novoComponente);
        }
        return true;
    }
    return false;
}

void Zona::adicionarPropriedades() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Propriedade *Fum = new Fumo(rand() % 100);
    propriedades.push_back(Fum);
    Propriedade *Hum = new Humidade(rand() % 100);
    propriedades.push_back(Hum);
    Propriedade *Lu = new Luz(rand() % 100);
    propriedades.push_back(Lu);
    Propriedade *Rad = new Radiacao(rand() % 100);
    propriedades.push_back(Rad);
    Propriedade *So = new Som(rand() % 100);
    propriedades.push_back(So);
    Propriedade *Tem = new Temperatura(rand() % (100 - (-272) + 1) + (-272));
    propriedades.push_back(Tem);
    Propriedade *Vib = new Vibracao(rand() % 100);
    propriedades.push_back(Vib);
}

void Zona::contaComponentes() {
    auto itS = sensores.begin();
    while(itS < sensores.end()){
        this->nSensores++;
        itS++;
    }

    auto itA = aparelhos.begin();
    while(itA < aparelhos.end()){
        this->nAparelhos++;
        itA++;
    }

    auto itP = processadores.begin();
    while(itP < processadores.end()){
        this->nProcessadores++;
        itP++;
    }
}

bool Zona::mudaComandoProcessador(int IDcomponente, string novoComando) {
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == IDcomponente){
            (*it)->setComando(novoComando);
            return true;
        }
        it++;
    }
    return false;
}

Propriedade *Zona::retornaPropriedade(string tipo) {
    auto it = propriedades.begin();
    while(it < propriedades.end()){
        if((*it)->getNome() == tipo){
            return *it;
        }
        it++;
    }

    return nullptr;
}

bool Zona::criaRegra(int IDprocessador, string tipoRegra, int IDsensor, float param1, float param2) {
    if(tipoRegra == "entre"){
        Regra *novaRegra = new Entre(retornaSensor(IDsensor), param1, param2);
        retornaProcessador(IDprocessador)->adicionaRegra(novaRegra);
        regras.push_back(novaRegra);
        return true;
    } else if(tipoRegra == "fora"){
        Regra *novaRegra = new Fora(retornaSensor(IDsensor), param1, param2);
        retornaProcessador(IDprocessador)->adicionaRegra(novaRegra);
        regras.push_back(novaRegra);
        return true;
    }

    return false;
}

bool Zona::criaRegra(int IDprocessador, string tipoRegra, int IDsensor, float param1) {
    if(tipoRegra == "iguala"){
        Regra *novaRegra = new IgualA(retornaSensor(IDsensor), param1);
        retornaProcessador(IDprocessador)->adicionaRegra(novaRegra);
        regras.push_back(novaRegra);
        return true;
    } else if(tipoRegra == "maiorque"){
        Regra *novaRegra = new MaiorQue(retornaSensor(IDsensor), param1);
        retornaProcessador(IDprocessador)->adicionaRegra(novaRegra);
        regras.push_back(novaRegra);
        return true;
    } else if(tipoRegra == "menorque"){
        Regra *novaRegra = new MenorQue(retornaSensor(IDsensor), param1);
        retornaProcessador(IDprocessador)->adicionaRegra(novaRegra);
        regras.push_back(novaRegra);
        return true;
    }

    return false;
}

Sensor *Zona::retornaSensor(int ID) {
    auto it = sensores.begin();
    while(it < sensores.end()){
        if((*it)->getIDnum() == ID){
            return *it;
        }
    }

    return nullptr;
}

Processador *Zona::retornaProcessador(int ID) {
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == ID){
            return *it;
        }
    }

    return nullptr;
}

Aparelho *Zona::retornaAparelho(int ID) {
    auto it = aparelhos.begin();
    while(it < aparelhos.end()){
        if((*it)->getIDnum() == ID){
            return *it;
        }
    }

    return nullptr;
}

string Zona::listaRegras(int IDprocessador) const {
    ostringstream buffer0;
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == IDprocessador){
            buffer0 << (*it)->listaRegras() << endl;
        }
        it++;
    }
    return buffer0.str();
}

bool Zona::removeRegra(int IDprocessador, int IDregra) {
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == IDprocessador){
            (*it)->removeRegra(IDregra);
            return true;
        }
        it++;
    }
    return false;
}

bool Zona::associaProcessadorAparelho(int IDprocessador, int IDaparelho) {
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == IDprocessador){
            (*it)->associaAparelho(retornaAparelho(IDaparelho));
            return true;
        }
        it++;
    }
    return false;
}

bool Zona::desassociaProcessadorAparelho(int IDprocessador, int IDaparelho) {
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == IDprocessador){
            (*it)->removeAparelho(IDaparelho);
            return true;
        }
        it++;
    }
    return false;
}

void Zona::avancaIteration() {
    auto itP = processadores.begin();
    while(itP < processadores.end()){
        (*itP)->avancaIteration();
        itP++;
    }
}

void Zona::enviaComandoManual(int IDaparelho, string comando) {
    auto it = aparelhos.begin();
    while(it < aparelhos.end()){
        if((*it)->getIDnum() == IDaparelho){
            if(comando == "liga"){
                if((*it)->getLigado() == true){
                    (*it)->efeitoSeLigado();
                } else if((*it)->getLigado() == false){
                    (*it)->efeitoSeLigado();
                    (*it)->setLigado(true);
                }
            } else if(comando == "desliga"){
                if((*it)->getLigado() == true){
                    (*it)->efeitoAoDesligar();
                    (*it)->setLigado(false);
                } else if((*it)->getLigado() == false){
                    return;
                }
            }
        }
        it++;
    }
}

string Zona::colocaLetra(int IDcomponente) {
    ostringstream buffer0;

    auto itS = sensores.begin();
    while(itS < sensores.end()){
        if((*itS)->getIDnum() == IDcomponente){
            buffer0 << (*itS)->getLetra() << (*itS)->getIDnum();
        }
        itS++;
    }

    auto itA = aparelhos.begin();
    while(itA < aparelhos.end()){
        if((*itA)->getIDnum() == IDcomponente){
            if((*itA)->getLigado() == true){
                buffer0 << toupper((*itA)->getLetra()) + (*itA)->getIDnum();
            } else if((*itA)->getLigado() == false){
                buffer0 << (*itA)->getLetra() << (*itA)->getIDnum();
            }
        }
        itA++;
    }

    auto itP = processadores.begin();
    while(itP < processadores.end()){
        if((*itP)->getIDnum() == IDcomponente){
            buffer0 << (*itP)->getLetra() << (*itP)->getIDnum();
        }
        itP++;
    }

    return buffer0.str();
}

string Zona::colocaLetrasTodas() {
    ostringstream buffer0;

    auto itS = sensores.begin();
    while(itS < sensores.end()){
        buffer0 << (*itS)->getLetra() << (*itS)->getIDnum() << " ";
        itS++;
    }

    auto itA = aparelhos.begin();
    while(itA < aparelhos.end()){
        if((*itA)->getLigado() == true){
            char c = (*itA)->getLetra();
            c = std::toupper(c);
            buffer0 << c << (*itA)->getIDnum();
        } else if((*itA)->getLigado() == false){
            buffer0 << (*itA)->getLetra() << (*itA)->getIDnum() << " ";
        }
        itA++;
    }

    auto itP = processadores.begin();
    while(itP < processadores.end()){
        buffer0 << (*itP)->getLetra() << (*itP)->getIDnum() << " ";
        itP++;
    }

    return buffer0.str();
}

Processador * Zona::copiarProcessador(int IDzona, int IDprocessador, string novoNome) {
    auto it = processadores.begin();
    while(it < processadores.end()){
        if((*it)->getIDnum() == IDprocessador){
            Processador* copiaProcessador = (*it)->clone();
            copiaProcessador->setNomeCopia(novoNome);
            copiaProcessador->setIDzonaCopia(IDzona);
            copiasProcessadores.push_back(copiaProcessador);
            return copiaProcessador;
        }
        it++;
    }
    return nullptr;
}

void Zona::ativarCopiasProcessador(string nome) {
    auto it = copiasProcessadores.begin();
    while(it < copiasProcessadores.end()){
        if((*it)->getNomeCopia() == nome){
            processadores.push_back(*it);
            copiasProcessadores.erase(it);
        }
        it++;
    }
}

#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

class Transporte {
private:
    int capacidade;
    int latencia;
    int intervalo;
    
public:
    Transporte(int capacidade, int latencia, int intervalo);
    
    int getCapacidade() const { return capacidade; }
    int getLatencia() const { return latencia; }
    int getIntervalo() const { return intervalo; }

};

#endif
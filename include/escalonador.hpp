#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "minHeap.hpp"

struct DadosTransporte {
    int origem;
    int destino;
};


class Escalonador {
private:
    MinHeap* heap;
    
public:
    Escalonador(int capacidadeMaxima);
    ~Escalonador();
    void InsereEvento(long long chave, int tempo, void* dados, int tipo);
    HeapItem* RetiraProximoEvento();
    
    bool Vazio();
};

#endif
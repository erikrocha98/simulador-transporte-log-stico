#include "escalonador.hpp"
#include <iostream>

Escalonador::Escalonador(int capacidadeMaxima) {
    heap = new MinHeap(capacidadeMaxima);
}

Escalonador::~Escalonador() {
    while (!heap->Vazio()) {
        HeapItem* item = heap->Remover();
        if (item != nullptr) {
            // Se dados é DadosTransporte, precisa deletar
            if (item->tipo == 2) {
                delete (DadosTransporte*) item->dados;
            }
            // Pacotes não deletamos aqui pois pertencem ao DadosSimulacao
            delete item;
        }
    }
    delete heap;
}

void Escalonador::InsereEvento(long long chave, int tempo, void* dados, int tipo) {
    // Passa direto para o heap. O heap que criará o HeapItem
    heap->Inserir(chave, tempo, dados, tipo);
}

HeapItem* Escalonador::RetiraProximoEvento() {
    if (!heap->Vazio()) {
        return heap->Remover();
    }
    return nullptr;
}

bool Escalonador::Vazio() {
    return heap->Vazio();
}
#include <iostream>
#include "pacote.hpp"

Pacote::Pacote(int id, int tempo, int origem, int destino) {
    this->id = id;
    this->tempoChegada = tempo;
    this->armazemOrigem = origem;
    this->armazemDestino = destino;
    this->armazemAtual = origem;
    this->tempoArmazenado = 0;
    this->tempoTransporte = 0;
    this->posicaoRota = 0;
    this->estadoAtual = NAO_POSTADO;
    this->rota = nullptr;
}


int Pacote::getId() const {
    return id;
}

int Pacote::getArmazemAtual() const {
    return armazemAtual;
}

int Pacote :: getArmazemOrigem() const {
    return armazemOrigem;
}

int Pacote::getTempoChegada() const {
    return tempoChegada;
}

int Pacote::getArmazemDestino() const {
    return armazemDestino;
}

EstadoPacote Pacote::getEstadoPacote() const {
    return estadoAtual;
}

void Pacote::definirRota(ListaEncadeada* caminho) {
    this->rota = caminho;
    this->posicaoRota = 1; // Começa no início da rota. começa em 1 porque estamos usando lista encadeada com célula cabeça
}

int Pacote::proximoDestino() {
    
    if (rota == nullptr) {
        std::cout << "  ERRO: Rota é NULL!" << std::endl;
        return -1;
    }
    
    if (chegouNoDestino()) {
        return -1;
    }
    
    if (posicaoRota + 1 > rota->getTamanho()) {
        std::cout << "  ERRO: Não há próximo na rota!" << std::endl;
        return -1;
    }
    
    int proximo = rota->getItem(posicaoRota + 1).getChave();
    
    return proximo;
}

void Pacote::avancarNaRota() {
    if (rota != nullptr && !chegouNoDestino()) {
        posicaoRota++;
        armazemAtual = rota->getItem(posicaoRota).getChave();
    }
}

bool Pacote::chegouNoDestino() const {
    return armazemAtual == armazemDestino;
    
}

void Pacote::atualizarEstado(EstadoPacote novoEstado) {
    estadoAtual = novoEstado;
}

void Pacote::registrarTempoArmazenado(int tempo) {
    tempoArmazenado += tempo;
}

void Pacote::registrarTempoTransporte(int tempo) {
    tempoTransporte += tempo;
}
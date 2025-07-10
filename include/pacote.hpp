#ifndef PACOTE_HPP
#define PACOTE_HPP
#include <iostream>
#include "listaEncadeada.hpp"

enum EstadoPacote {
    NAO_POSTADO = 1,
    CHEGADA_ESCALONADA = 2,
    ARMAZENADO = 3,
    REMOVIDO = 4,
    ENTREGUE = 5
};

class Pacote {
    public:
        Pacote(int id, int tempo, int origem, int destino);
        
        int getId() const;
        int getArmazemAtual() const;
        int getArmazemOrigem() const;
        int getArmazemDestino() const;
        int getTempoChegada() const;
        int proximoDestino();
        EstadoPacote getEstadoPacote() const;

        void avancarNaRota();      
        void atualizarEstado(EstadoPacote novo_estado);
        void definirRota(ListaEncadeada* caminho);
        bool chegouNoDestino() const;
        
        void registrarTempoArmazenado(int tempo);
        void registrarTempoTransporte(int tempo);
        

    private:
        int id;
        int tempoChegada;
        int tempoArmazenado;
        int tempoTransporte;
        int armazemOrigem;
        int armazemDestino;
        int armazemAtual;
        int posicaoRota;
        EstadoPacote estadoAtual;
        ListaEncadeada* rota;
    
};

#endif
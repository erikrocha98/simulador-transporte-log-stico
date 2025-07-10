#ifndef PILHA_HPP
#define PILHA_HPP
#include <iostream>
#include "pacote.hpp"

class Pilha
{
    public:
        Pilha();
        ~Pilha();
        bool Vazia();
        void Empilha(Pacote* item);
        int GetTamanho();
        Pacote* Desempilha();
        void Limpa();
        Pacote* GetPrimeiro();
    private:
        int topo;
        int tamanho;
        static const int MAXTAM = 1000;
        Pacote* itens[MAXTAM];
};


#endif
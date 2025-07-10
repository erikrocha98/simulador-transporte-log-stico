#include <iostream>
#include "pilha.hpp"

Pilha :: Pilha (){
    topo = -1;
    tamanho = 0;
}

Pilha :: ~Pilha(){
    Limpa();
}

void Pilha::Empilha(Pacote* item){
    if(tamanho == MAXTAM)
        throw "A pilha está cheia!";
    topo++;
    itens[topo] = item;
    tamanho++;
};

Pacote* Pilha::Desempilha(){
    Pacote* aux;
    
    if(tamanho == 0)
        throw "A pilha está vazia!";
    
    aux = itens[topo];
    topo--;
    tamanho--;
    return aux;
};
Pacote* Pilha::GetPrimeiro() {
    if (tamanho == 0) {
        return nullptr;
    }
    return itens[topo];
};

void Pilha :: Limpa(){
    topo=-1;
    tamanho=0;
};

bool Pilha :: Vazia (){
    return tamanho == 0;
};

int Pilha :: GetTamanho(){
    return tamanho;
}


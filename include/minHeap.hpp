#ifndef MINHEAP_HPP
#define MINHEAP_HPP
#include <iostream>

struct HeapItem {
    long long chave;
    void* dados;
    int tipo; // 1=pacote, 2=transporte
    int tempo;         
};

class MinHeap
{
public:
    MinHeap(int maxsize);
    ~MinHeap();
    void Inserir(long long chave, int tempo, void* dados, int tipo);
    HeapItem* Remover();
    bool Vazio();
    int getTamanho ();

private:
    int GetAncestral(int posicao);
    int GetSucessorEsq(int posicao);
    int GetSucessorDir(int posicao);
    int tamanho;
    int capacidade;
    HeapItem *data;
    void HeapifyPorBaixo(int posicao);
    void HeapifyPorCima(int posicao);
};

#endif
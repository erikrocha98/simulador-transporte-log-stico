#include <iostream>
#include "minHeap.hpp"

MinHeap ::MinHeap(int maxsize)
{
    this->tamanho = 0;
    this->capacidade= maxsize;
    this->data = new HeapItem[maxsize];
};

MinHeap ::~MinHeap()
{
    delete[] data;
};

int MinHeap ::GetAncestral(int i)
{
    return (i - 1) / 2;
};
int MinHeap ::GetSucessorEsq(int i)
{
    return 2 * i + 1;
};
int MinHeap ::GetSucessorDir(int i)
{
    return 2 * i + 2;
};
int MinHeap :: getTamanho (){
    return tamanho;
};

bool MinHeap ::Vazio()
{
    if (tamanho == 0)
    {
        return 1;
    }
    return 0;
};

void MinHeap ::HeapifyPorCima(int posicao)
{
    int i = posicao;
    int p = GetAncestral(i);
    HeapItem aux;
    while (i>0 && data[i].chave < data[p].chave)
    {
        aux = data[i];
        data[i] = data[p];
        data[p] = aux;
        i = p;
        p = (i - 1) / 2;
    }
};

void MinHeap ::HeapifyPorBaixo(int posicao)
{
    int i = posicao;
    HeapItem aux;                   
    while (true)
    {
        int sucessor_esq = GetSucessorEsq(i);
        int sucessor_dir = GetSucessorDir(i);
        int s;

        if (sucessor_esq >= tamanho)
            break; // Se não tem filhos, para

        if (sucessor_dir >= tamanho)
        { // Só filho esquerdo
            s = sucessor_esq;
        }
        else
        {
            s = (data[sucessor_esq].chave < data[sucessor_dir].chave) ? sucessor_esq : sucessor_dir; // índice do menor sucessor de i
        }

        if (data[i].chave > data[s].chave)
        {   
            aux = data[i];
            data[i] = data[s];
            data[s] = aux;                              
            i = s;                       
        }
        else
        {
            break; // Se já estiver no lugar certo, para
        }
    }
};

void MinHeap::Inserir(long long chave, int tempoReal, void* dados, int tipo) {
    if (tamanho >= capacidade) {
        throw "Heap cheio!";
    }
    
    data[tamanho].chave = chave;
    data[tamanho].tempo = tempoReal;
    data[tamanho].dados = dados;
    data[tamanho].tipo = tipo;
    
    HeapifyPorCima(tamanho);
    tamanho++;
}


HeapItem* MinHeap::Remover() {
    if (tamanho == 0) {
        return nullptr;
    }
    
    HeapItem* valor_removido = new HeapItem();
    *valor_removido = data[0];  // Copia o item do topo
    
    data[0] = data[tamanho - 1];
    tamanho--;
    
    if (tamanho > 0) {
        HeapifyPorBaixo(0);
    }
    
    return valor_removido;
}
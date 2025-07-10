#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP
#include <iostream>

typedef int TipoChave;

class TipoItem
{
public:
    TipoItem();
    TipoItem(TipoChave c);
    void setChave(TipoChave c);
    TipoChave getChave();
    void imprime();

private:
    TipoChave chave;
};

class TipoCelula
{
public:
    TipoCelula();

private:
    TipoItem item;
    TipoCelula *prox;
    friend class ListaEncadeada;
};

class ListaEncadeada
{
public:
    ListaEncadeada();
    ~ListaEncadeada();
    TipoItem getItem(int pos);
    void setItem(TipoItem item, int pos);
    int getTamanho();
    void insere_inicio(TipoItem item);
    void insere_final(TipoItem item);
    TipoItem remove_inicio();
    void imprime();
    void limpa();
    bool contemElemento(int v);

private:
    TipoCelula *primeiro;
    TipoCelula *ultimo;
    TipoCelula *posiciona(int pos, bool antes);
    int tamanho;
};

#endif
#include <iostream>
#include "listaEncadeada.hpp"

TipoItem ::TipoItem()
{
    chave = -1;
};
TipoItem ::TipoItem(TipoChave c)
{
    chave = c;
};

void TipoItem ::setChave(TipoChave c)
{
    chave = c;
};

TipoChave TipoItem ::getChave()
{
    return chave;
};

void TipoItem ::imprime()
{
    std::cout << chave;
};

TipoCelula ::TipoCelula()
{
    item.setChave(-1);
    prox = nullptr;
};

ListaEncadeada ::ListaEncadeada()
{
    primeiro = new TipoCelula();
    ultimo = primeiro;
    tamanho = 0;
};

TipoCelula *ListaEncadeada::posiciona(int pos, bool antes = false)
{
    TipoCelula *p;
    int i;
    if ((pos > tamanho) || (pos < 0)){
        std::cerr << "DEBUG: pos = " << pos << ", tamanho = " << tamanho << std::endl;
        throw std::runtime_error("ERRO: Posicao Invalida!");
    }
    // Posiciona na célula anterior a desejada
    p = primeiro;
    for (i = 1; i < pos; i++)
    {
        p = p->prox;
    }
    // vai para a próxima
    // se antes for false
    if (!antes)
        p = p->prox;
    return p;
};

TipoItem ListaEncadeada :: getItem(int pos)
{
    TipoCelula *p;
    p = posiciona(pos);
    return p->item;
};

void ListaEncadeada :: setItem(TipoItem item, int pos){
    TipoCelula *p;
    p=posiciona(pos);
    p->item = item;
};
void ListaEncadeada ::insere_inicio(TipoItem item)
{
    TipoCelula *nova_celula;
    nova_celula = new TipoCelula();
    nova_celula->item = item;
    nova_celula->prox = primeiro->prox;
    primeiro->prox = nova_celula;
    tamanho++;
    if (tamanho == 1)
    {
        ultimo = nova_celula;
    }
};
void ListaEncadeada ::insere_final(TipoItem item)
{
    TipoCelula *nova_celula;
    nova_celula = new TipoCelula();
    nova_celula->item = item;
    ultimo->prox = nova_celula;
    ultimo = nova_celula;
    tamanho++;
};
TipoItem ListaEncadeada ::remove_inicio()
{
    TipoItem aux;
    TipoCelula *p;
    if (tamanho == 0)
    {
        throw std::runtime_error("ERRO: Lista Vazia!");
    }
    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;
    if (primeiro->prox == nullptr)
        ultimo = primeiro;
    aux = p->item;
    delete (p);
    return aux;
};
void ListaEncadeada ::imprime()
{
    TipoCelula *p;
    p = primeiro->prox;
    while (p != nullptr)
    {
        p->item.imprime();
        std::cout <<" ";
        p = p->prox;
    }
};
void ListaEncadeada::limpa()
{
    TipoCelula *p;
    p = primeiro->prox;
    while (p != nullptr)
    {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
};
int ListaEncadeada :: getTamanho(){
    return tamanho;
};

bool ListaEncadeada :: contemElemento(int v){
    TipoCelula* atual = primeiro->prox;  // assumindo que 'primeiro' é célula cabeça

    while (atual != nullptr) {
        if (atual->item.getChave() == v) {
            return true;
        }
        atual = atual->prox;
    }

    return false;
};

ListaEncadeada ::~ListaEncadeada()
{
    limpa();
    delete primeiro;
};
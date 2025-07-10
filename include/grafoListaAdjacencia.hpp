#ifndef GRAFOADJACENCIA_HPP
#define GRAFOADJACENCIA_HPP
#include "listaEncadeada.hpp"

//Fila circular como estrutura auxiliar para busca em largura.
class FilaCircular {
    public:
        FilaCircular();
        void enfileira(TipoItem item);
        TipoItem desenfileira();
        void limpa();
        int getTamanho() const;
        bool vazia() const;

    private:
        int frente;
        int tras;
        int tamanho;
        static const int MAXTAM = 100;
        TipoItem itens[MAXTAM];    
};

class NoVertice {
    public:
        int id; //identificador pro vértice que estaremos adicionando as arestas
        ListaEncadeada vertices_adjacentes;
        NoVertice* prox; //apontador para o próximo vértice na lista de adjacencias.
        NoVertice(int id);
        ~NoVertice();
};

class ListaAdjacencia {
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();

        void insereVertice();
        void insereAresta(int v, int w);
        int quantidadeVertices();
        int quantidadeArestas();
        int grau(int v);
        void imprimeVizinhos(int v);

    private: 
        NoVertice* primeiro;
        NoVertice* ultimo;
        int numVertices;
        int numArestas;

        NoVertice* buscaVertice(int id);
    
    friend class GrafoListaAdjacencia;

};

class GrafoListaAdjacencia{
    public:
        GrafoListaAdjacencia();
        ~GrafoListaAdjacencia();

        void InsereVertice();
        void InsereAresta(int v, int w);

        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();
        int GrauVertice(int v);

        void ImprimeVizinhos(int v);
        bool ExisteAresta(int v, int w);

        ListaEncadeada* CalculaMenorCaminho (int origem, int destino);
        
    private:
        ListaAdjacencia vertices;
};

#endif
#include <iostream>
#include "grafoListaAdjacencia.hpp"

// Implementação Fila Circular
FilaCircular ::FilaCircular()
{
    frente = 0;
    tras = 0;
    tamanho = 0;
};

int FilaCircular ::getTamanho() const
{
    return tamanho;
};

bool FilaCircular ::vazia() const
{
    return tamanho == 0;
}

void FilaCircular::enfileira(TipoItem item)
{
    if (tamanho == MAXTAM)
        throw "Fila Cheia!";
    itens[tras] = item;
    tras = (tras + 1) % MAXTAM;
    tamanho++;
};

TipoItem FilaCircular::desenfileira()
{
    TipoItem aux;
    if (tamanho == 0)
        throw "Fila está vazia!";
    aux = itens[frente];
    frente = (frente + 1) % MAXTAM;
    tamanho--;
    return aux;
};

void FilaCircular ::limpa()
{
    tamanho = 0;
    frente = 0;
    tras = 0;
}

/* ---------------------------------------------------------------------------------------------------------------------------------- */

// Implementação da Lista de Adjacências
NoVertice ::NoVertice(int id)
{
    this->id = id;
    this->prox = nullptr;
};
NoVertice ::~NoVertice() {};

ListaAdjacencia ::ListaAdjacencia()
{
    primeiro = nullptr;
    ultimo = nullptr;
    numVertices = 0;
    numArestas = 0;
};
ListaAdjacencia ::~ListaAdjacencia()
{
    NoVertice *atual = primeiro;
    while (atual != nullptr)
    {
        NoVertice *aux = atual;
        atual = atual->prox;
        delete aux;
    }
}
void ListaAdjacencia ::insereVertice()
{
    NoVertice *novo_vertice = new NoVertice(numVertices);
    if (primeiro == nullptr)
    {
        primeiro = novo_vertice;
    }
    else
    {
        ultimo->prox = novo_vertice;
    }
    ultimo = novo_vertice;
    numVertices++;
};
NoVertice *ListaAdjacencia::buscaVertice(int id)
{
    NoVertice *atual = primeiro;
    while (atual != nullptr)
    {
        if (atual->id == id)
            return atual;
        atual = atual->prox;
    }
    return nullptr;
};

void ListaAdjacencia::insereAresta(int v, int w)
{
    NoVertice *verticeV = buscaVertice(v);
    NoVertice *verticeW = buscaVertice(w);

    if (!verticeV || !verticeW)
        throw std::runtime_error("Vértice não encontrado");

    verticeV->vertices_adjacentes.insere_final(TipoItem(w));
    verticeW->vertices_adjacentes.insere_final(TipoItem(v));

    numArestas++;
};
int ListaAdjacencia ::quantidadeVertices()
{
    return numVertices;
};
int ListaAdjacencia ::quantidadeArestas()
{
    return numArestas;
};
int ListaAdjacencia::grau(int v)
{
    NoVertice *vertice = buscaVertice(v);
    if (!vertice)
        throw std::runtime_error("Vértice não encontrado");

    return vertice->vertices_adjacentes.getTamanho();
};
void ListaAdjacencia::imprimeVizinhos(int v)
{
    NoVertice *vertice = buscaVertice(v);
    if (!vertice)
        throw std::runtime_error("Vértice não encontrado");

    vertice->vertices_adjacentes.imprime();
    std::cout << std::endl;
};

/* ---------------------------------------------------------------------------------------------------------------------------------- */
// Implementação do Grafo

GrafoListaAdjacencia ::GrafoListaAdjacencia() {};
GrafoListaAdjacencia ::~GrafoListaAdjacencia() {};

void GrafoListaAdjacencia ::InsereVertice()
{
    vertices.insereVertice();
};
void GrafoListaAdjacencia ::InsereAresta(int v, int w)
{
    vertices.insereAresta(v, w);
};
int GrafoListaAdjacencia ::QuantidadeVertices()
{
    return vertices.quantidadeVertices();
};
int GrafoListaAdjacencia ::QuantidadeArestas()
{
    return vertices.quantidadeArestas();
};
int GrafoListaAdjacencia ::GrauMinimo()
{
    if (vertices.quantidadeVertices() == 0)
        return 0;

    int min = vertices.grau(0);
    for (int i = 1; i < vertices.quantidadeVertices(); i++)
    {
        if (vertices.grau(i) < min)
        {
            min = vertices.grau(i);
        }
    }
    return min;
};
int GrafoListaAdjacencia ::GrauMaximo()
{
    if (vertices.quantidadeVertices() == 0)
        return 0;

    int max = vertices.grau(0);
    for (int i = 1; i < vertices.quantidadeVertices(); i++)
    {
        if (vertices.grau(i) > max)
        {
            max = vertices.grau(i);
        }
    }
    return max;
};

int GrafoListaAdjacencia ::GrauVertice(int v)
{
    return vertices.grau(v);
};

void GrafoListaAdjacencia ::ImprimeVizinhos(int v)
{
    vertices.imprimeVizinhos(v);
};

bool GrafoListaAdjacencia ::ExisteAresta(int v, int w)
{
    NoVertice *vertice = vertices.buscaVertice(v);

    if (vertice == nullptr)
    {
        return false;
    }

    // Verifica se o vértice w está na lista de adjacência de v
    return vertice->vertices_adjacentes.contemElemento(w);
};

/* ---------------------------------------------------------------------------------------------------------------------------------- */
//Implementação da busca em largura

ListaEncadeada *GrafoListaAdjacencia::CalculaMenorCaminho(int origem, int destino)
{
    // Verifica se os vértices existem
    if (origem < 0 || origem >= vertices.quantidadeVertices() ||
        destino < 0 || destino >= vertices.quantidadeVertices())
    {
        std::cerr << "Erro: vértices inválidos" << std::endl;
        return nullptr;
    }

    // Arrays auxiliares
    bool *visitado = new bool[vertices.quantidadeVertices()];
    int *predecessor = new int[vertices.quantidadeVertices()];

    // Inicializar
    for (int i = 0; i < vertices.quantidadeVertices(); i++)
    {
        visitado[i] = false;
        predecessor[i] = -1;
    }

    FilaCircular fila;

    visitado[origem] = true;
    fila.enfileira(origem);

    bool encontrou = false;

    try
    {
        while (fila.getTamanho() > 0)
        {
            TipoItem atual = fila.desenfileira();
            if (atual.getChave() == destino)
            {
                encontrou = true;
                break;
            }
            NoVertice *verticeAtual = vertices.buscaVertice(atual.getChave());
            if (verticeAtual == nullptr)
            {
                std::cerr << "  ERRO: Vértice " << atual.getChave()
                          << " não encontrado!" << std::endl;
                continue;
            }

            
            // Percorre todos os vizinhos
            int numVizinhos = verticeAtual->vertices_adjacentes.getTamanho();

            for (int i = 1; i <= numVizinhos; i++)
            {
                TipoItem itemVizinho = verticeAtual->vertices_adjacentes.getItem(i);
                int vizinho = itemVizinho.getChave();

                if (!visitado[vizinho])
                {
                    visitado[vizinho] = true;
                    predecessor[vizinho] = atual.getChave();
                    fila.enfileira(vizinho);
                }
            }
        }
    }
    catch (const char *e)
    {
        delete[] visitado;
        delete[] predecessor;
        return nullptr;
    }

    //Lista para receber o caminho
    ListaEncadeada *caminho = new ListaEncadeada();

    if (!encontrou && origem != destino)
    {
        delete[] visitado;
        delete[] predecessor;
        return caminho; // retorna lista vazia
    }

    // Reconstrói o caminho do destino até a origem
    if (origem == destino)
    {
        // Caso especial: origem igual ao destino
        caminho->insere_final(TipoItem(origem));
    }
    else
    {
        // pilha auxiliar para inverter o caminho
        int *caminhoTemp = new int[vertices.quantidadeVertices()];
        int tamanhoCaminho = 0;

        int atual = destino;
        while (atual != -1)
        {
            caminhoTemp[tamanhoCaminho++] = atual;
            atual = predecessor[atual];
        }

        // Insere na lista na ordem correta (origem -> destino)
        for (int i = tamanhoCaminho - 1; i >= 0; i--)
        {
            caminho->insere_final(TipoItem(caminhoTemp[i]));
        }

        delete[] caminhoTemp;
    }

    delete[] visitado;
    delete[] predecessor;

    return caminho;
}
#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "pilha.hpp"
#include "pacote.hpp"

class Armazem
{
public:
    Armazem(int id, int numConexoes);
    ~Armazem();

    void armazenarPacote(Pacote *pacote, int secaoDestino);
    Pacote *removerPacote(int secao);

    int encontrarSecao(int armazemDestino);
    bool secaoVazia(int secao);
    int calcularTempoRemocao(int secao, int custoBase);

    void configurarConexaoArmazens(int secao, int idVizinho);
    int getId() const;
    int getNumConexoes() const;
    void imprimirConexoes() const;
    Pilha* getSecao(int secao);

private:
    int id;
    int numConexoes;
    Pilha **secoes;  // Array de ponteiros para pilhas. Uma forma de representar seções dentro dos armazéns.
    int *idConexoes; // Array com IDs dos armazéns conectados
};

#endif

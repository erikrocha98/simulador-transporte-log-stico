#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include "escalonador.hpp"
#include "armazem.hpp"
#include "pacote.hpp"
#include "transporte.hpp"
#include "grafoListaAdjacencia.hpp"
#include <iostream>
#include <fstream>

// Estrutura para todos os dados da simulação
struct DadosSimulacao
{
    // Parâmetros
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransportes;
    int custoRemocao;

    // Topologia
    int numArmazens;
    GrafoListaAdjacencia *grafo;
    Armazem **armazens;

    // Pacotes
    int numPacotes;
    Pacote **pacotes;
};

class VetorEstatico
{
public:
    VetorEstatico();
    Pacote* GetItem(int pos);
    int GetTamanho();
    void InsereFinal(Pacote* pacote);
    Pacote* RemoveFinal();
    void Limpa();

private:
    static const int MAXTAM = 1000;
    Pacote* pacotes[MAXTAM];
    int tamanho;
};

class Simulacao
{

public:
    Simulacao(DadosSimulacao *dados);
    Simulacao();
    ~Simulacao();

    void executar();
    DadosSimulacao *lerArquivoEntrada(const char *nomeArquivo);

private:
    const int TEMPO_MAXIMO_SIMULACAO = 100000;
    DadosSimulacao *dados;
    Escalonador *escalonador;
    Transporte *transporte;
    int relogioAtual;
    int tempoPrimeiroPacote;

    void inicializarEventosTransporte();
    void inicializarEventosPacotes();
    void processarEventoPacote(HeapItem *evento);
    void processarEventoTransporte(HeapItem *evento);
    bool todasSecoesVazias();
    void imprimirEvento(int tempo, const std::string &mensagem);

    // Funções para criar chaves
    long long criarChavePacote(int tempo, int idPacote);
    long long criarChaveTransporte(int tempo, int origem, int destino);

};

#endif
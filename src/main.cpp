#include <iostream>
#include <fstream>
#include <sstream>

#include "motorSimulacao.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Uso: ./tp2.out <arquivo_entrada>" << std::endl;
        return 1;
    }
        
    Simulacao simulacao_leitura;
    DadosSimulacao* dados = simulacao_leitura.lerArquivoEntrada(argv[1]);
    
    if (dados == nullptr) {
        std::cout << "Erro ao ler arquivo!" << std::endl;
        return 1;
    }
    
    Simulacao* simulacao = new Simulacao(dados);
    simulacao->executar();
    
    delete simulacao;
    
    return 0;
}
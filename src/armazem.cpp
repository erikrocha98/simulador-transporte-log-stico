#include "armazem.hpp"

Armazem::Armazem(int id, int numConexoes) {
    this->id = id;
    this->numConexoes = numConexoes;
    
    // Cria array de pilhas
    secoes = new Pilha*[numConexoes];
    idConexoes = new int[numConexoes];
    
    // Inicializa cada pilha
    for (int i = 0; i < numConexoes; i++) {
        secoes[i] = new Pilha();
        idConexoes[i] = -1;
    }
}

Armazem::~Armazem() {
    for (int i = 0; i < numConexoes; i++) {
        delete secoes[i];
    }
    delete[] secoes;
    delete[] idConexoes;
}

bool Armazem :: secaoVazia(int secao){
    if (secoes[secao]->GetTamanho() ==0){
        return true;
    }
    return false;
};

int Armazem :: getNumConexoes() const{
    return numConexoes;
};

//Método para debug
void Armazem::imprimirConexoes() const {
    std::cout << "Armazém " << id << " conexões:" << std::endl;
    for (int i = 0; i < numConexoes; i++) {
        std::cout << "  Seção " << i << " -> Armazém " << idConexoes[i] << std::endl;
    }
};

void Armazem::armazenarPacote(Pacote* pacote, int secaoDestino) {
    // Encontrar qual seção corresponde ao destino para que o pacote possa ser armazenado
    int secao = encontrarSecao(secaoDestino);
    if (secao != -1) {
        secoes[secao]->Empilha(pacote);
    }
}

Pacote* Armazem::removerPacote(int secao) {
    if (!secaoVazia(secao)) {
        return (Pacote*) secoes[secao]->Desempilha();
    }
    return nullptr;
}

void Armazem::configurarConexaoArmazens(int secao, int idVizinho) {
    if (secao >= 0 && secao < numConexoes) {      
        idConexoes[idVizinho] = idVizinho;
    }
}

int Armazem::encontrarSecao(int destino) {
    // Garante que o Id do armazén coincida com a seção destino
    if (destino >= 0 && destino < numConexoes && idConexoes[destino] != -1) {
        return destino;
    }
    
    // Debug caso a seção não seja encontrada
    std::cout << "DEBUG: Armazém " << id << " procurando seção para destino " 
              << destino << std::endl;
    std::cout << "  Conexões disponíveis: ";
    for (int i = 0; i < numConexoes; i++) {
        std::cout << idConexoes[i] << " ";
    }
    std::cout << std::endl;
    
    return -1;
}

int Armazem::calcularTempoRemocao(int secao, int custoBase) {
    return (custoBase * secoes[secao]->GetTamanho());
};

Pilha* Armazem::getSecao(int secao) {
    if (secao < 0 || secao >= numConexoes) {
        return nullptr;
    }
    return secoes[secao];
}
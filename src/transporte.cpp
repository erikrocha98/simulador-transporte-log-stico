#include <iostream>
#include "transporte.hpp"

Transporte :: Transporte (int capacidade, int latencia, int intervalo){
    this->capacidade = capacidade;
    this->latencia = latencia;
    this->intervalo = intervalo;
}
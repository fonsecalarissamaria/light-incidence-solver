#include "Obstacle.h"

/*
    Arquivo: Obstacle.cpp
    Propósito: Implementa a classe base Obstacle.
    
    Funcionalidades Principais:
    - Inicialização de obstáculos com identificador e taxa de redução
    - Fornecimento de métodos de acesso aos atributos básicos
 */

Obstacle::Obstacle(int id, double rate)
    : id(id), reductionRate(rate) {}

int Obstacle::getId() const {
    return id;
}

double Obstacle::getReductionRate() const {
    return reductionRate;
}
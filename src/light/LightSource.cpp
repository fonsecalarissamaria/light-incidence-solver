#include "LightSource.h"

/*
    Arquivo: LightSource.cpp
    Propósito: Implementa o construtor da estrutura LightSource.
    
    Funcionalidade Principal:
    - Inicializa uma fonte de luz com identificador, intensidade e posição
 */

LightSource::LightSource(int id, double intensity, const Point& position)
    : id(id), intensity(intensity), position(position) {}
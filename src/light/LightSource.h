#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../geometry/Point.h"

/*
    Arquivo: LightSource.h
    Propósito: Define a estrutura de uma fonte de luz utilizada na simulação.
    
    Funcionalidade Principal:
    - Representação de uma fonte de luz com identificador, intensidade e posição
 */

struct LightSource {
    int id;
    double intensity;
    Point position;

    LightSource(int id, double intensity, const Point& position);
};

#endif
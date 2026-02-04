#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../geometry/Point.h"

/*
    Arquivo: Obstacle.h
    Propósito: Declara a classe base abstrata Obstacle para os diferentes tipos de obstáculos.
    
    Funcionalidades Principais:
    - Definição da interface comum para obstáculos geométricos
    - Declaração de métodos virtuais para interseção e contenção
    - Armazenamento de identificador e taxa de redução de luminosidade
 */

struct Segment;

class Obstacle {
public:
    Obstacle(int id, double rate);
    virtual ~Obstacle() = default;

    // ideia geral: todo obstaculo saberá contar suas interseções
    virtual int countIntersections(const Segment& ray) const = 0;

    // todo obstáculo deverá saber se um ponto está dentro dele
    virtual bool contains(const Point& p) const = 0;

    // acessores
    int getId() const;
    double getReductionRate() const;

protected:
    int id;
    double reductionRate;
};

#endif
#ifndef CIRCLE_H
#define CIRCLE_H

#include "Obstacle.h"
#include "../geometry/Point.h"

/*
    Arquivo: Circle.h
    Propósito: Declara a classe Circle, representando um obstáculo circular no ambiente 2D.
    
    Funcionalidades Principais:
    - Representação de obstáculos circulares com posição e raio
    - Declaração das operações de interseção e contenção de pontos
 */

class Circle : public Obstacle {
public:
    Circle(int id, double rate, const Point& center, double radius);

    int countIntersections(const Segment& ray) const override;
    bool contains(const Point& p) const override;

private:
    Point center;
    double radius;
};

#endif
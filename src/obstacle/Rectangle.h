#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Obstacle.h"
#include "../geometry/Point.h"
#include "../geometry/Segment.h"

/*
    Arquivo: Rectangle.h
    Propósito: Declara a classe Rectangle, representando um obstáculo retangular no ambiente 2D.
    
    Funcionalidades Principais:
    - Representação de obstáculos retangulares definidos por origem, largura e altura
    - Declaração das operações de interseção e verificação de contenção de pontos
 */

class Rectangle : public Obstacle {
public:
    Rectangle(int id, double rate, const Point& origin, double width, double height);

    int countIntersections(const Segment& ray) const override;
    bool contains(const Point& p) const override;

private:
    Point origin;
    double width;
    double height;
};

#endif
#ifndef LINE_H
#define LINE_H

#include "Obstacle.h"
#include "../geometry/Segment.h"

/*
    Arquivo: Line.h
    Propósito: Declara a classe Line, representando um obstáculo linear no ambiente 2D.
    
    Funcionalidades Principais:
    - Representação de obstáculos do tipo linha por meio de um segmento
    - Declaração das operações de interseção e verificação de contenção
 */

class Line : public Obstacle {
public:
    Line(int id, double rate, const Segment& line);

    int countIntersections(const Segment& ray) const override;
    bool contains(const Point& p) const override;

private:
    Segment line;
};

#endif
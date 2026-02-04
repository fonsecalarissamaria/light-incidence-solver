#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.h"

/*
    Arquivo: Segment.h
    Propósito: Define a estrutura de um segmento de reta em 2D a partir de dois pontos.
    
    Funcionalidade Principal:
    - Representação de um segmento por seus pontos inicial e final
 */

struct Segment {
    Point a;
    Point b;

    // Construtor
    Segment(const Point& p1, const Point& p2);
};

#endif
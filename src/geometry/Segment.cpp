#include "Segment.h"

/*
    Arquivo: Segment.cpp
    Propósito: Implementa o construtor da estrutura Segment.
    
    Funcionalidade Principal:
    - Inicializa um segmento de reta a partir de dois pontos
 */

Segment::Segment(const Point& p1, const Point& p2)
    : a(p1), b(p2) {}
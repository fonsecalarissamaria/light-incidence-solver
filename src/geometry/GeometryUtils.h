#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include "Point.h"
#include "Segment.h"

/*
    Arquivo: GeometryUtils.h
    Propósito: Declara funções utilitárias de geometria usadas nos cálculos 
    
    Funcionalidades Principais:
    - Cálculo de distâncias entre pontos
    - Cálculo da distância entre ponto e segmento
    - Verificação de interseção entre segmentos de reta
    - Cálculo de interseções entre segmento e círculo
 */

namespace GeometryUtils {

    // Calcula a distância Euclidiana entre dois pontos
    double distance(const Point& p1, const Point& p2);

    
    // Calcula a menor distância entre um ponto P e um segmento S 
    double pointLineDistance(const Point& p, const Segment& s);

    
    // Verifica se dois segmentos se cruzam (incluindo nas extremidade)
    bool intersects(const Segment& s1, const Segment& s2);

    
    // Calcula quantas vezes um segmento intercepta um círculo.
    // OBS: Considerei tolerância (Epsilon) para casos de borda. 
    int segmentCircleIntersections(const Segment& s, const Point& center, double radius);
}

#endif
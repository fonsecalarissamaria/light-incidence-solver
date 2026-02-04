#include "Circle.h"
#include "../geometry/GeometryUtils.h"

/*
    Arquivo: Circle.cpp
    Propósito: Implementa o obstáculo circular e sua lógica de interseção.
    
    Funcionalidades Principais:
    - Inicialização de obstáculos circulares
    - Cálculo de interseções entre raios e círculos
    - Verificação de pertencimento de um ponto ao círculo
 */

Circle::Circle(int id, double rate, const Point& center, double radius)
    : Obstacle(id, rate), center(center), radius(radius) {}

int Circle::countIntersections(const Segment& ray) const {
    // para melhor organização, deleguei o cálculo para o utils
    return GeometryUtils::segmentCircleIntersections(ray, center, radius);
}

bool Circle::contains(const Point& p) const {
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    
    // compara o quadrado da distância pra evitar a raiz quadrada e calcular mais rápido
    return (dx * dx + dy * dy) <= (radius * radius);
}
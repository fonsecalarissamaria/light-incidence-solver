#include "Circle.h"
#include "../geometry/GeometryUtils.h"

Circle::Circle(int id, double rate, const Point& center, double radius)
    : Obstacle(id, rate), center(center), radius(radius) {}

int Circle::countIntersections(const Segment& ray) const {
    // Delega o cálculo matemático para a utils
    return GeometryUtils::segmentCircleIntersections(ray, center, radius);
}

bool Circle::contains(const Point& p) const {
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    
    // Compara o quadrado da distância pra evitar a raiz quadrada (mais rápido)
    return (dx * dx + dy * dy) <= (radius * radius);
}
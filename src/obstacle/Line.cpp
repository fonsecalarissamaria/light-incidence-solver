#include "Line.h"
#include "../geometry/GeometryUtils.h"
#include <cmath>
#include <algorithm>

/*
    Arquivo: Line.cpp
    Propósito: Implementa o obstáculo linear e sua lógica de interseção.
    
    Funcionalidades Principais:
    - Inicialização de obstáculos do tipo linha
    - Cálculo de interseções entre raios e segmentos de reta
    - Verificação de pertencimento de um ponto à linha
 */


// tolerância para evitar erros de ponto flutuante
static const double EPSILON = 1e-5;

Line::Line(int id, double rate, const Segment& line)
    : Obstacle(id, rate), line(line) {}

// função pra interseção paramétrica 
static bool checkLineIntersection(const Segment& ray, const Segment& wall) {
    double x1 = ray.a.x, y1 = ray.a.y;
    double x2 = ray.b.x, y2 = ray.b.y;
    double x3 = wall.a.x, y3 = wall.a.y;
    double x4 = wall.b.x, y4 = wall.b.y;

    double den = (x1- x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    // Se o denominador é zero, as retas são paralelas
    if (std::abs(den) < EPSILON) return false;

    double t = ((x1 - x3) * (y3 -y4) - (y1 - y3) * (x3 - x4)) / den;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1- x3)) / den;

    // verifica se a interseção ocorre dentro dos segmentos [0, 1] e usa epsilon para detectar pontas e quinas
    if (t >= -EPSILON && t <= 1.0 + EPSILON && 
        u >= -EPSILON && u <= 1.0 + EPSILON) {
        return true;
    }

    return false;
}

int Line::countIntersections(const Segment& ray) const {
    return checkLineIntersection(ray, line) ? 1 : 0;
}

bool Line::contains(const Point& p) const {
    return GeometryUtils::pointLineDistance(p, line) <= EPSILON;
}
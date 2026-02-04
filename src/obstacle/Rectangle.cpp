#include "Rectangle.h"
#include "../geometry/GeometryUtils.h"
#include <vector>
#include <cmath>
#include <algorithm>

// tolerância para quinas e bordas
static const double EPSILON = 1e-5;

Rectangle::Rectangle(int id, double rate, const Point& origin, double width, double height)
    : Obstacle(id, rate), origin(origin), width(width), height(height) {}

// função pra interseção paramétrica 
static bool getSegmentIntersection(const Segment& s1, const Segment& s2, Point& intersection) {
    double x1 = s1.a.x, y1 = s1.a.y;
    double x2 = s1.b.x, y2 = s1.b.y;
    double x3 = s2.a.x, y3 = s2.a.y;
    double x4 = s2.b.x, y4 = s2.b.y;

    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    // retas paralelas
    if (std::abs(den) < EPSILON) return false;

    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    // verifica se interseção ocorre dentro dos segmentos [0, 1] com a tolerância
    if (t >= -EPSILON && t <= 1.0 + EPSILON && 
        u >= -EPSILON && u <= 1.0 + EPSILON) {
        
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);
        return true;
    }

    return false;
}

int Rectangle::countIntersections(const Segment& ray) const {
    // define os 4 vértices do retângulo
    Point p1 = origin;
    Point p2 = {origin.x + width, origin.y};
    Point p3 = {origin.x + width, origin.y + height};
    Point p4 = {origin.x, origin.y + height};

    // define as 4 arestas
    Segment edges[4] = {
        {p1, p2}, // topo
        {p2, p3}, // direita
        {p3, p4}, // baixa
        {p4, p1}  // esquerda
    };

    std::vector<Point> hits;

    // coleta as interseções
    for (int i = 0; i < 4; ++i) {
        Point hitPoint;
        if (getSegmentIntersection(ray, edges[i], hitPoint)) {
            hits.push_back(hitPoint);
        }
    }

    if (hits.empty()) return 0;

    // filtra duplicatas (no caso do raio bater exatamente na quina)
    int uniqueCount = 0;
    for (size_t i = 0; i < hits.size(); ++i) {
        bool isDuplicate = false;
        
        // compara com os pontos já contabilizados
        for (size_t j = 0; j < i; ++j) {
            if (GeometryUtils::distance(hits[i], hits[j]) < EPSILON) {
                isDuplicate = true;
                break;
            }
        }
        
        if (!isDuplicate) uniqueCount++;
    }

    return uniqueCount;
}

bool Rectangle::contains(const Point& p) const {
    // verifica bounding box com tolerância inclusiva
    return p.x >= origin.x - EPSILON && p.x <= origin.x + width + EPSILON &&
           p.y >= origin.y - EPSILON && p.y <= origin.y + height + EPSILON;
}
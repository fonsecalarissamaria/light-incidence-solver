#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../geometry/Point.h"

// Forward declaration para evitar include desnecessário aqui
struct Segment;

class Obstacle {
public:
    Obstacle(int id, double rate);
    virtual ~Obstacle() = default;

    // Contrato: todo obstáculo deve saber contar suas interseções
    virtual int countIntersections(const Segment& ray) const = 0;

    // Contrato: todo obstáculo deve saber se um ponto está dentro dele
    virtual bool contains(const Point& p) const = 0;

    // Acessores
    int getId() const;
    double getReductionRate() const;

protected:
    int id;
    double reductionRate;
};

#endif
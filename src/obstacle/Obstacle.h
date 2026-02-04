#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../geometry/Point.h"

struct Segment;

class Obstacle {
public:
    Obstacle(int id, double rate);
    virtual ~Obstacle() = default;

    // ideia geral: todo obstaculo saberá contar suas interseções
    virtual int countIntersections(const Segment& ray) const = 0;

    // todo obstáculo deverá saber se um ponto está dentro dele
    virtual bool contains(const Point& p) const = 0;

    // acessores
    int getId() const;
    double getReductionRate() const;

protected:
    int id;
    double reductionRate;
};

#endif
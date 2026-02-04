#ifndef CIRCLE_H
#define CIRCLE_H

#include "Obstacle.h"
#include "../geometry/Point.h"

class Circle : public Obstacle {
public:
    Circle(int id, double rate, const Point& center, double radius);

    int countIntersections(const Segment& ray) const override;
    bool contains(const Point& p) const override;

private:
    Point center;
    double radius;
};

#endif
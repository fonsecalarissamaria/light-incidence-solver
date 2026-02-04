#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Obstacle.h"
#include "../geometry/Point.h"
#include "../geometry/Segment.h"

class Rectangle : public Obstacle {
public:
    Rectangle(int id, double rate, const Point& origin, double width, double height);

    int countIntersections(const Segment& ray) const override;
    bool contains(const Point& p) const override;

private:
    Point origin;
    double width;
    double height;
};

#endif
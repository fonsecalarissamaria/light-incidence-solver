#ifndef LINE_H
#define LINE_H

#include "Obstacle.h"
#include "../geometry/Segment.h"

class Line : public Obstacle {
public:
    Line(int id, double rate, const Segment& line);

    int countIntersections(const Segment& ray) const override;
    bool contains(const Point& p) const override;

private:
    Segment line;
};

#endif
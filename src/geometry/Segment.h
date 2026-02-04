#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.h"

struct Segment {
    Point a;
    Point b;

    // Construtor
    Segment(const Point& p1, const Point& p2);
};

#endif
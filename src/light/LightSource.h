#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "../geometry/Point.h"

struct LightSource {
    int id;
    double intensity;
    Point position;

    LightSource(int id, double intensity, const Point& position);
};

#endif
#include "Obstacle.h"

Obstacle::Obstacle(int id, double rate)
    : id(id), reductionRate(rate) {}

int Obstacle::getId() const {
    return id;
}

double Obstacle::getReductionRate() const {
    return reductionRate;
}
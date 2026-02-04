#ifndef REGION_H
#define REGION_H

#include <vector>
#include <memory>
#include "../geometry/Point.h"
#include "../light/LightSource.h"
#include "../obstacle/Obstacle.h"

/*
    Arquivo: Region.h
    Propósito: Declara a estrutura responsável por representar uma região do cenário.
    
    Funcionalidades Principais:
    - Armazenamento de fontes de luz, obstáculos e pontos de consulta
    - Interface para adição dos elementos que compõem o ambiente
 */

// armazena os pontos onde será calculado a luz
struct PointQuery {
    int id;
    Point position;
};

class Region {
public:
    // armazena tudoo do cenário
    std::vector<LightSource> lights;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    std::vector<PointQuery> points;

    // adiciona obstáculos
    void addRectangle(int id, int reduction, int x, int y, int height, int width);
    void addCircle(int id, int reduction, int x, int y, int radius);
    void addLine(int id, int reduction, int x1, int y1, int x2, int y2);

    // adiciona luzes e pontos
    void addLightSource(int id, double intensity, int x, int y);
    void addPoint(int id, int x, int y);
};

#endif
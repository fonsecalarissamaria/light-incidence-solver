#ifndef REGION_H
#define REGION_H

#include <vector>
#include <memory>
#include "../geometry/Point.h"
#include "../light/LightSource.h"
#include "../obstacle/Obstacle.h"

// Estrutura auxiliar para armazenar os pontos onde calcularemos a luz
struct PointQuery {
    int id;
    Point position;
};

class Region {
public:
    // Armazena as entidades do cenário
    std::vector<LightSource> lights;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    std::vector<PointQuery> points;

    // Métodos para adicionar Obstáculos
    // Note que corrigi os nomes dos parâmetros para refletir o que são (reduction)
    void addRectangle(int id, int reduction, int x, int y, int height, int width);
    void addCircle(int id, int reduction, int x, int y, int radius);
    void addLine(int id, int reduction, int x1, int y1, int x2, int y2);

    // Métodos para adicionar Luzes e Pontos
    void addLightSource(int id, double intensity, int x, int y);
    void addPoint(int id, int x, int y);
};

#endif
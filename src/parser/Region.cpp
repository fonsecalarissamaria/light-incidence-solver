#include "Region.h"

// Includes das implementações concretas (necessários apenas aqui)
#include "../obstacle/Rectangle.h"
#include "../obstacle/Circle.h"
#include "../obstacle/Line.h"
#include "../geometry/Segment.h"

// -------------------- Adição de Obstáculos --------------------

void Region::addRectangle(int id, int reduction, int x, int y, int height, int width) {
    // ATENÇÃO: O arquivo de entrada fornece (Height, Width).
    // Mas o construtor do Rectangle espera (Width, Height).
    // Por isso invertemos a ordem na chamada abaixo.
    obstacles.push_back(
        std::make_shared<Rectangle>(
            id,
            static_cast<double>(reduction),
            Point{static_cast<double>(x), static_cast<double>(y)},
            static_cast<double>(width),  // Largura vem primeiro no construtor
            static_cast<double>(height)  // Altura vem depois
        )
    );
}

void Region::addCircle(int id, int reduction, int x, int y, int radius) {
    obstacles.push_back(
        std::make_shared<Circle>(
            id,
            static_cast<double>(reduction),
            Point{static_cast<double>(x), static_cast<double>(y)},
            static_cast<double>(radius)
        )
    );
}

void Region::addLine(int id, int reduction, int x1, int y1, int x2, int y2) {
    Segment segment(
        Point{static_cast<double>(x1), static_cast<double>(y1)},
        Point{static_cast<double>(x2), static_cast<double>(y2)}
    );

    obstacles.push_back(
        std::make_shared<Line>(
            id,
            static_cast<double>(reduction),
            segment
        )
    );
}

// -------------------- Adição de Luzes --------------------

void Region::addLightSource(int id, double intensity, int x, int y) {
    lights.emplace_back(
        id,
        intensity,
        Point{static_cast<double>(x), static_cast<double>(y)}
    );
}

// -------------------- Adição de Pontos de Consulta --------------------

void Region::addPoint(int id, int x, int y) {
    points.push_back(
        PointQuery{
            id,
            Point{static_cast<double>(x), static_cast<double>(y)}
        }
    );
}
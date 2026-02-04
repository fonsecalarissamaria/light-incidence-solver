#include "Region.h"
#include "../obstacle/Rectangle.h"
#include "../obstacle/Circle.h"
#include "../obstacle/Line.h"
#include "../geometry/Segment.h"

// Adição dos obstáculos: 

void Region::addRectangle(int id, int reduction, int x, int y, int height, int width) {
    obstacles.push_back(
        std::make_shared<Rectangle>(
            id,
            static_cast<double>(reduction),
            Point{static_cast<double>(x), static_cast<double>(y)},
            static_cast<double>(width),  
            static_cast<double>(height) 
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

// Adição das luzes:

void Region::addLightSource(int id, double intensity, int x, int y) {
    lights.emplace_back(
        id,
        intensity,
        Point{static_cast<double>(x), static_cast<double>(y)}
    );
}

// Adição dos pontos de consulta

void Region::addPoint(int id, int x, int y) {
    points.push_back(
        PointQuery{
            id,
            Point{static_cast<double>(x), static_cast<double>(y)}
        }
    );
}
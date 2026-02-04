#include "GeometryUtils.h"
#include <cmath>
#include <algorithm>
#include <limits>

namespace GeometryUtils {

    // Tolerância para lidar com imprecisões de ponto flutuante (usei para encontrar tangentes)
    static const double EPSILON = 1e-5;

    
    // Funçoes de Distância: 

    double distance(const Point& p1, const Point& p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    double pointLineDistance(const Point& p, const Segment& s) {
        double x0 = p.x, y0 = p.y;
        double x1 = s.a.x, y1 = s.a.y;
        double x2 = s.b.x, y2 = s.b.y;

        double dx = x2 - x1;
        double dy = y2 - y1;

        // se o segmento for um ponto: 
        if (std::abs(dx) < EPSILON && std::abs(dy) < EPSILON) {
            return distance(p, s.a);
        }

        // projeção do ponto sobre a reta suporte 
        double t = ((x0 - x1) * dx + (y0 - y1) * dy) / (dx * dx + dy * dy);

        // garante que a projeção caia DENTRO do segmento [0, 1]
        t = std::max(0.0, std::min(1.0, t));

        // encontra o ponto que está mais próximo no segmento
        Point closest = { x1 + t * dx, y1 + t * dy };

        return distance(p, closest);
    }

    // Interseção de Segmentos:

    // retorna: 0 se for colinear, 1 se horário e 2 se for anti-horário
    static int orientation(const Point& p, const Point& q, const Point& r) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

        if (std::abs(val) < EPSILON) return 0; 
        return (val > 0) ? 1 : 2;
    }

    // verifica se o ponto q está no segmento pr 
    static bool onSegment(const Point& p, const Point& q, const Point& r) {
        return q.x <= std::max(p.x, r.x) + EPSILON && q.x >= std::min(p.x, r.x) - EPSILON &&
               q.y <= std::max(p.y, r.y) + EPSILON && q.y >= std::min(p.y, r.y) - EPSILON;
    }

    bool intersects(const Segment& s1, const Segment& s2) {
        Point p1 = s1.a, q1 = s1.b;
        Point p2 = s2.a, q2 = s2.b;

        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q2);

        // caso geral (orientações diferentes indicam cruzamento)
        if (o1 != o2 && o3 != o4) return true;

        // casos especiais (colinearidade e sobreposição)
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false;
    }

    // Interseção com Círculo: 

    int segmentCircleIntersections(const Segment& s, const Point& center, double radius) {
        // interseção reta com círculo
        double dx = s.b.x - s.a.x;
        double dy = s.b.y - s.a.y;
        double fx = s.a.x - center.x;
        double fy = s.a.y - center.y;

        double A = dx * dx + dy * dy;
        double B = 2 * (fx * dx + fy * dy);
        double C = (fx * fx + fy * fy) - radius * radius;

        double discriminant = B * B - 4 * A * C;

        // sem interseção real
        if (discriminant < -EPSILON) return 0;

        // tangente exata (considerando discriminante próximo de 0)
        if (std::abs(discriminant) < EPSILON) discriminant = 0;

        double sqrtDisc = std::sqrt(discriminant);
        
        // as duas soluções para t 
        double t1 = (-B - sqrtDisc) / (2 * A);
        double t2 = (-B + sqrtDisc) / (2 * A);

        int count = 0;

        // verifica se t1 está dentro do segmento [0 1]
        if (t1 >= -EPSILON && t1 <= 1.0 + EPSILON) {
            count++;
        }

        // verifica t2 (mas só conta se for distinto de t1 pra evitar duplicar a tangente)
        if (std::abs(t1 - t2) > EPSILON) {
            if (t2 >= -EPSILON && t2 <= 1.0 + EPSILON) {
                count++;
            }
        }

        return count;
    }

} 
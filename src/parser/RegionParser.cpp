#include "RegionParser.h"

#include <fstream>
#include <sstream>
#include <iostream>

RegionParser::RegionParser(const std::string& filename)
    : filename(filename) {}

Region RegionParser::parse() {
    Region region;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Erro] Nao foi possivel abrir o arquivo: " << filename << std::endl;
        return region; // Retorna região vazia em caso de erro
    }

    std::string line;
    while (std::getline(file, line)) {
        // Ignora linhas vazias
        if (line.empty()) continue;

        std::stringstream ss(line);
        char command;
        ss >> command; // Lê o identificador do comando (R, C, L, F, P)

        // Switch é mais limpo e rápido que vários 'if-else'
        switch (command) {
            case 'R': { // Retângulo
                int id, reduction, x, y, h, w;
                if (ss >> id >> reduction >> x >> y >> h >> w) {
                    region.addRectangle(id, reduction, x, y, h, w);
                }
                break;
            }
            case 'C': { // Círculo
                int id, reduction, x, y, radius;
                if (ss >> id >> reduction >> x >> y >> radius) {
                    region.addCircle(id, reduction, x, y, radius);
                }
                break;
            }
            case 'L': { // Linha
                int id, reduction, x1, y1, x2, y2;
                if (ss >> id >> reduction >> x1 >> y1 >> x2 >> y2) {
                    region.addLine(id, reduction, x1, y1, x2, y2);
                }
                break;
            }
            case 'F': { // Fonte de Luz
                int id, x, y;
                double intensity;
                if (ss >> id >> intensity >> x >> y) {
                    region.addLightSource(id, intensity, x, y);
                }
                break;
            }
            case 'P': { // Ponto de Consulta
                int id, x, y;
                if (ss >> id >> x >> y) {
                    region.addPoint(id, x, y);
                }
                break;
            }
            default:
                // Se encontrar um comando desconhecido, apenas ignora
                break;
        }
    }

    return region;
}
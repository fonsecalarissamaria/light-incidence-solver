#include "RegionParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

/*
    Arquivo: RegionParser.cpp
    Propósito: Implementa o parser responsável por carregar uma região a partir de arquivo.
    
    Funcionalidades Principais:
    - Leitura e interpretação do arquivo de entrada
    - Criação de obstáculos, fontes de luz e pontos de consulta
    - Montagem da estrutura Region a partir dos comandos lidos
 */

RegionParser::RegionParser(const std::string& filename)
    : filename(filename) {}

Region RegionParser::parse() {
    Region region;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Erro] Nao foi possivel abrir o arquivo: " << filename << std::endl;
        return region; // retorna região vazia só em caso de erro
    }

    std::string line;
    while (std::getline(file, line)) {
        // ignora linhas vazias
        if (line.empty()) continue;

        std::stringstream ss(line);
        char command;
        ss >> command; // lê os identificadores do comando (R, C, L, F, P )

        switch (command) {
            case 'R': { // retangulo 
                int id, reduction, x, y, h, w;
                if (ss >> id >> reduction >> x >> y >> h >> w) {
                    region.addRectangle(id, reduction, x, y, h, w);
                }
                break;
            }
            case 'C': { // circulo
                int id, reduction, x, y, radius;
                if (ss >> id >> reduction >> x >> y >> radius) {
                    region.addCircle(id, reduction, x, y, radius);
                }
                break;
            }
            case 'L': { // linha
                int id, reduction, x1, y1, x2, y2;
                if (ss >> id >> reduction >> x1 >> y1 >> x2 >> y2) {
                    region.addLine(id, reduction, x1, y1, x2, y2);
                }
                break;
            }
            case 'F': { // fonte de luz
                int id, x, y;
                double intensity;
                if (ss >> id >> intensity >> x >> y) {
                    region.addLightSource(id, intensity, x, y);
                }
                break;
            }
            case 'P': { // ponto para calcular a luminosidade 
                int id, x, y;
                if (ss >> id >> x >> y) {
                    region.addPoint(id, x, y);
                }
                break;
            }
            default:
                // ignora comandos desconhecidos 
                break;
        }
    }

    return region;
}
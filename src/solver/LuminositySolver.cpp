#include "LuminositySolver.h"
#include "../geometry/GeometryUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <sys/stat.h> 

/*
    Arquivo: LuminositySolver.cpp
    Propósito: Implementa a lógica de cálculo da luminosidade final em cada
               ponto da região, considerando fontes de luz e obstáculos.

    Responsabilidades:
    - Garantir a existência do diretório de saída
    - Calcular o fator de redução de luz causado por obstáculos
    - Somar as contribuições de todas as fontes de luz
    - Gerar o arquivo final com os valores de luminosidade por ponto
 */

// garante que o diretório de saída existe 
static void ensureDirectoryExists(const std::string& path) {
    struct stat info;
    
    // caso não consiga acessar o caminho
    if (stat(path.c_str(), &info) != 0) {
        // tenta criar com permissões de leitura,escrita,execução (0777)
        if (mkdir(path.c_str(), 0777) != 0) {
            perror(("Erro ao criar pasta: " + path).c_str());
        } else {
            std::cout << "Pasta criada: " << path << std::endl;
        }
    } 
    else if (!(info.st_mode & S_IFDIR)) {
        std::cerr << "[Aviso] " << path << " existe, mas nao e um diretorio!" << std::endl;
    }
}

// calcula o fator de redução acumulado para um raio específico
static double calculateObstacleReduction(
    const Segment& ray,
    const std::vector<std::shared_ptr<Obstacle>>& obstacles
) {
    double factor = 1.0;

    for (const auto& obs : obstacles) {
        // conta quantas vezes o raio atravessa ou toca o obstaculo
        int intersections = obs->countIntersections(ray);

        if (intersections > 0) {
            // converte porcentagem para decimal
            double reductionRate = obs->getReductionRate() / 100.0;
            
            // aplica a redução exponencialmente baseada no número de interseções
            factor *= std::pow(1.0 - reductionRate, intersections);
        }
    }

    return factor;
}


LuminositySolver::LuminositySolver(const Region& r)
    : region(r) {}

void LuminositySolver::solve(const std::string& exampleName) const {
    const std::string outputDir = "saidas-luminosidades-finais";
    ensureDirectoryExists(outputDir);

    std::string filePath = outputDir + "/luminosidades-finais-" + exampleName + ".txt";
    std::ofstream outFile(filePath);

    if (!outFile.is_open()) {
        std::cerr << "Erro: Nao foi possivel criar o arquivo " << filePath << std::endl;
        return;
    }

    // processa cada ponto de consulta da região
    for (const auto& point : region.points) {
        double totalIntensity = 0.0;

        // soma cada fonte de luz
        for (const auto& light : region.lights) {
            Segment ray(light.position, point.position);

            // verifica barreiras
            double reductionFactor = calculateObstacleReduction(ray, region.obstacles);

            // intensidade final = intensidade original * fator de redução
            totalIntensity += light.intensity * reductionFactor;
        }

        // formatação da saída
        outFile << "P" << point.id << " = "
                << std::fixed << std::setprecision(2)
                << totalIntensity << std::endl;
    }

    outFile.close();
    std::cout << "Relatorio gerado com sucesso: " << filePath << std::endl;
}
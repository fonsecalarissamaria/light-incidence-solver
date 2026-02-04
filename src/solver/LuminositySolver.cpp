#include "LuminositySolver.h"
#include "../geometry/GeometryUtils.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <sys/stat.h> // Para mkdir e stat (Linux/Unix)

// -------------------------------------------------------------------------
// Funções Auxiliares (Internas ao módulo)
// -------------------------------------------------------------------------

// Garante que o diretório de saída exista
static void ensureDirectoryExists(const std::string& path) {
    struct stat info;
    
    // Se não consegue acessar o caminho (provavelmente não existe)
    if (stat(path.c_str(), &info) != 0) {
        // Tenta criar com permissões de leitura/escrita/execução (0777)
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

// Calcula o fator de redução acumulado para um raio específico
static double calculateObstacleReduction(
    const Segment& ray,
    const std::vector<std::shared_ptr<Obstacle>>& obstacles
) {
    double factor = 1.0;

    for (const auto& obs : obstacles) {
        // Conta quantas vezes o raio atravessa ou toca o obstáculo
        int intersections = obs->countIntersections(ray);

        if (intersections > 0) {
            // Converte porcentagem (0-100) para decimal (0.0-1.0)
            double reductionRate = obs->getReductionRate() / 100.0;
            
            // Aplica a redução exponencialmente baseada no número de interseções
            factor *= std::pow(1.0 - reductionRate, intersections);
        }
    }

    return factor;
}

// -------------------------------------------------------------------------
// Implementação da Classe LuminositySolver
// -------------------------------------------------------------------------

LuminositySolver::LuminositySolver(const Region& r)
    : region(r) {}

void LuminositySolver::solve(const std::string& exampleName) const {
    const std::string outputDir = "saidas-luminosidades-finais";
    ensureDirectoryExists(outputDir);

    std::string filePath = outputDir + "/luminosidades-finais-" + exampleName + ".txt";
    std::ofstream outFile(filePath);

    if (!outFile.is_open()) {
        std::cerr << "Erro fatal: Nao foi possivel criar o arquivo " << filePath << std::endl;
        return;
    }

    // Processa cada ponto de consulta da região
    for (const auto& point : region.points) {
        double totalIntensity = 0.0;

        // Soma a contribuição de cada fonte de luz
        for (const auto& light : region.lights) {
            Segment ray(light.position, point.position);

            // Verifica barreiras no caminho
            double reductionFactor = calculateObstacleReduction(ray, region.obstacles);

            // Intensidade Final = Intensidade Original * Fator de Redução
            // (Nota: A distância não atenua a luz neste modelo físico específico)
            totalIntensity += light.intensity * reductionFactor;
        }

        // Formatação da saída: P{ID} = {VALOR}
        outFile << "P" << point.id << " = "
                << std::fixed << std::setprecision(2)
                << totalIntensity << std::endl;
    }

    outFile.close();
    std::cout << "Relatorio gerado com sucesso: " << filePath << std::endl;
}
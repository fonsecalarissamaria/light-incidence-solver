#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <dirent.h>     
#include <sys/stat.h>   
#include <sys/types.h>
#include <unistd.h>
#include "parser/RegionParser.h"
#include "solver/LuminositySolver.h"

// Configurações Globais
const std::string INPUT_DIR_NAME = "exemplos";
const std::string OUTPUT_DIR_NAME = "saidas-larissa"; // teste para visualizar a região 

// Funções Auxiliares de Sistema:

// código para garantir o diretório de saída, a fim de conferir os resultados 
void ensureDirectoryExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        if (mkdir(path.c_str(), 0777) != 0) {
            perror(("[Erro] Falha ao criar pasta " + path).c_str());
            exit(EXIT_FAILURE); // Encerra se não conseguir criar a pasta
        }
        std::cout << "[Sistema] Pasta criada: " << path << std::endl;
    } 
    else if (!(info.st_mode & S_IFDIR)) {
        std::cerr << "[Aviso] " << path << " existe, mas nao e um diretorio!" << std::endl;
    }
}

// Funções de debug

// gera um arquivo de texto com o estado atual da região para validação
void debugExportRegion(const Region& region, const std::string& outputFile) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        perror(("[Erro] Nao foi possivel criar arquivo " + outputFile).c_str());
        return;
    }

    out << "=== LUZES ===\n";
    for (const auto& light : region.lights) {
        out << "ID: " << light.id 
            << " Pos: (" << light.position.x << "," << light.position.y << ")"
            << " Intensidade: " << light.intensity << "\n";
    }

    out << "\n=== OBSTACULOS ===\n";
    for (const auto& obs : region.obstacles) {
        out << "Obstacle ID: " << obs->getId() << "\n";
    }

    out << "\n=== PONTOS DE CONSULTA ===\n";
    for (const auto& point : region.points) {
        out << "ID: " << point.id 
            << " Pos: (" << point.position.x << "," << point.position.y << ")\n";
    }

    out.close();
    std::cout << "Arquivo gerado: " << outputFile << std::endl;
}

// leitura de Diretório:

// retorna lista filtrada e ordenada dos exemplos
std::vector<std::string> getExampleList(const std::string& basePath) {
    std::vector<std::string> examples;
    DIR* dir = opendir(basePath.c_str());

    if (!dir) {
        std::cerr << "[Erro Fatal] Nao foi possivel abrir a pasta: " << basePath << std::endl;
        exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        
        // ignora "." e ".." e seleciona apenas os que começam com "exemplo"
        if (name == "." || name == "..") continue;
        if (name.rfind("exemplo", 0) == 0) {
            examples.push_back(name);
        }
    }
    closedir(dir);

    // ordena para garantir processamento sequencial (exemplo1, exemplo2..)
    std::sort(examples.begin(), examples.end());
    return examples;
}

int main() {

    // preparação do ambiente
    ensureDirectoryExists(OUTPUT_DIR_NAME);

    // busca lista de tarefas
    std::vector<std::string> exemplos = getExampleList(INPUT_DIR_NAME);

    if (exemplos.empty()) {
        std::cout << "Nenhum exemplo encontrado em " << INPUT_DIR_NAME << std::endl;
        return 0;
    }

    // executa processamento
    for (const auto& nomeExemplo : exemplos) {
        std::string inputPath = INPUT_DIR_NAME + "/" + nomeExemplo + "/regiao.txt";
        
        //std::cout << "\n--------------------------------------------------" << std::endl;
        std::cout << "\nProcessando: " << nomeExemplo << std::endl;

        // parsing
        RegionParser parser(inputPath);
        Region region = parser.parse();

        // exportação de debug
        std::string debugFile = OUTPUT_DIR_NAME + "/" + nomeExemplo + "_region.txt";
        debugExportRegion(region, debugFile);

        // cálculo da luminosidade 
        LuminositySolver solver(region);
        solver.solve(nomeExemplo);
    }

    //std::cout << "\n=== CONCLUIDO COM SUCESSO ===" << std::endl;
    return 0;
}
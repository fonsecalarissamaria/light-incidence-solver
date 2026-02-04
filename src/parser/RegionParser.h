#ifndef REGION_PARSER_H
#define REGION_PARSER_H

#include <string>
#include "Region.h"

// Classe responsável por interpretar o arquivo de entrada e criar a cena
class RegionParser {
public:
    // Construtor explícito para evitar conversões acidentais
    explicit RegionParser(const std::string& filename);

    // Lê o arquivo e retorna a estrutura Region totalmente populada
    Region parse();

private:
    std::string filename;
};

#endif
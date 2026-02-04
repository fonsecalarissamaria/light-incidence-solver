#ifndef REGION_PARSER_H
#define REGION_PARSER_H

#include <string>
#include "Region.h"

// interpreta o arquivo de entrada e cria a cena
class RegionParser {
public:
    // construtor 
    explicit RegionParser(const std::string& filename);

    // lê o arquivo e retorna a estrutura Region
    Region parse();

private:
    std::string filename;
};

#endif
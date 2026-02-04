#ifndef REGION_PARSER_H
#define REGION_PARSER_H

#include <string>
#include "Region.h"

/*
    Arquivo: RegionParser.h
    Propósito: Declara a classe responsável por interpretar o arquivo de entrada
               e construir a estrutura da cena (Region).

    Responsabilidades:
    - Armazenar o nome do arquivo de entrada
    - Realizar o parsing do arquivo
    - Retornar a região construída
 */

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
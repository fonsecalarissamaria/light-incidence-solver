#ifndef LUMINOSITY_SOLVER_H
#define LUMINOSITY_SOLVER_H

#include <string>
#include "../parser/Region.h"

/*
    Arquivo: LuminositySolver.h
    Propósito: Declara a classe responsável por calcular a luminosidade final
               em pontos específicos da região, a partir das fontes de luz
               e dos obstáculos presentes no cenário.

    Responsabilidades:
    - Armazenar a região a ser analisada
    - Executar o cálculo de luminosidade em cada ponto
    - Gerar o relatório final de saída
 */

class LuminositySolver {
public:
    // recebe a região já carregada com obstáculos e luzes
    explicit LuminositySolver(const Region& region);

    // executa os cálculos e salva o relatório no arquivo de saída
    void solve(const std::string& exampleName) const;

private:
    Region region;
};

#endif
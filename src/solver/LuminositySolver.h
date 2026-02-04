#ifndef LUMINOSITY_SOLVER_H
#define LUMINOSITY_SOLVER_H

#include <string>
#include "../parser/Region.h"

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
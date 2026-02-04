# Light Incidence Solver

Este projeto implementa um código em C++ para calcular a intensidade de luz em ambientes 2D. O sistema simula a propagação de raios de luz a partir de múltiplas fontes, calculando a atenuação causada pela interseção com obstáculos geométricos (retângulos, círculos e linhas).

## Estrutura do Código

O código fonte está organizado na pasta `src` e separado por responsabilidades:

* **src/geometry**: Primitivas matemáticas e álgebra vetorial necessárias para os cálculos espaciais.
* **src/obstacle**: Definição das classes de obstáculos e implementação da lógica de interseção de raios.
* **src/parser**: Módulo responsável pela leitura, interpretação e carregamento dos arquivos de entrada.
* **src/solver**: Núcleo do projeto, contendo a classe `LuminositySolver` que executa o algoritmo de ray casting e aplica os fatores de redução.

## Compilação e Execução

O projeto utiliza Make para gerenciamento de compilação.

1. Para compilar o projeto, execute o comando na raiz:

```bash
make
```

2. Para executar o programa:

```bash
./luminosidade
```

## Verificação dos Resultados

Após a execução bem-sucedida, o programa criará automaticamente dois diretórios na raiz do projeto contendo os relatórios de processamento:

### saidas-luminosidades-finais/ (Resultado Principal)
Este diretório contém os resultados finais do cálculo. Cada arquivo de texto apresenta a intensidade de luz calculada para cada ponto de interesse, já considerando as reduções impostas pelos obstáculos.

### saidas-regioes/ (Debug e Conferência)
Este diretório é gerado para fins de validação. Ele contém uma transcrição dos dados lidos pelo parser (posições das luzes, coordenadas dos obstáculos e pontos), servindo para conferir se a entrada foi carregada corretamente antes do processamento.
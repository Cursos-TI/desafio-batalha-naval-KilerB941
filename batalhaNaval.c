// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para abs()

#define TAMANHO_TABULEIRO 10
#define TAMANHO_MATRIZ_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para criar a matriz de habilidade Cone
void criarMatrizCone(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            if (i <= j && i + j < TAMANHO_MATRIZ_HABILIDADE) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade Cruz
void criarMatrizCruz(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]) {
    int centro = TAMANHO_MATRIZ_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade Octaedro
void criarMatrizOctaedro(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]) {
    int centro = TAMANHO_MATRIZ_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int offset = TAMANHO_MATRIZ_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            int linhaTabuleiro = linhaOrigem - offset + i;
            int colunaTabuleiro = colunaOrigem - offset + j;
            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO &&
                habilidade[i][j] == 1) {
                tabuleiro[linhaTabuleiro][colunaTabuleiro] = 5; // Marca área afetada
            }
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf("A "); // Área afetada
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posicionar navios no tabuleiro (exemplo)
    tabuleiro[2][3] = 3; // Navio horizontal
    tabuleiro[5][6] = 3; // Navio vertical

    // Definir matrizes de habilidade
    int cone[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    int cruz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    int octaedro[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    int linhaOrigemCone = 4, colunaOrigemCone = 4;
    int linhaOrigemCruz = 7, colunaOrigemCruz = 7;
    int linhaOrigemOctaedro = 9, colunaOrigemOctaedro = 9;

    aplicarHabilidade(tabuleiro, cone, linhaOrigemCone, colunaOrigemCone);
    aplicarHabilidade(tabuleiro, cruz, linhaOrigemCruz, colunaOrigemCruz);
    aplicarHabilidade(tabuleiro, octaedro, linhaOrigemOctaedro, colunaOrigemOctaedro);

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
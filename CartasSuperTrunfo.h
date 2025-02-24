#pragma once

#define MAX_CARTAS 4

typedef struct {
    char codigoEstado;
    int codigoCidade;
    char nomeCidade[100];
    char uf[3];
    unsigned long int populacao;
    double area;
    double pib;
    int pontosTuristicos;
    double densidadePopulacional;
    double pibPerCapita;
    float superPoder;
} Carta;

void cabecalho();
void cadastrarCarta();
void gerarCodigoCarta(char codigoEstado, int codigoCidade, char nomeCidade[100], char uf[3]);
double calcDensidadePopulacional(unsigned long int populacao, double area);
double calcPibPerCapita(double pib, unsigned long int populacao);
void compararCartas();
float calcularSuperPoder(Carta carta);
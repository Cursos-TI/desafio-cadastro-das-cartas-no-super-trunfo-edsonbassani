#pragma once
void cadastrarCarta();
void cabecalho();
void gerarCodigoCarta(char codigoEstado, int codigoCidade, char nomeCidade[100], char uf[3]);
double calcDensidadePopulacional(unsigned long int populacao, double area);
double calcPibPerCapita(double pib, unsigned long int populacao);

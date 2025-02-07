#include <stdio.h>
#include "CartasSuperTrunfo.h"

void cabecalho() {
    printf("***********************************\n");
    printf("************ MateCheck ************\n");
    printf("***********************************\n");
    printf("****** Super Trunfo - Países ******\n");
    printf("***********************************\n");
    printf("************* Bem-vindo ***********\n");
    printf("***********************************\n");
    printf("******* Cadastro de Cartas ********\n");
    printf("***********************************\n");
}

double calcDensidadePopulacional(double populacao, double area) {
    if (area == 0) {
        printf("Erro: Área não pode ser zero.\n");
        return 0;
    }
    return (populacao / area);
}

double calcPibPerCapita(double pib, double populacao) {
    if (populacao == 0) {
        printf("Erro: População não pode ser zero.\n");
        return 0;
    }
    return (pib / populacao);
}

void cadastrarCarta() {
    char codigoEstado;
    char uf[3];
    char nomeCidade[100];
    int codigoCidade, pontosTuristicos;
    double populacao, area, pib, densidadePopulacional, pibPerCapita;

    cabecalho();

    printf("Informe o Código do Estado (A-H):\n");
    scanf(" %c", &codigoEstado);

    // Verificação do código do estado
    if (codigoEstado < 'A' || codigoEstado > 'H') {
        printf("Erro: Código do estado inválido.\n");
        return;
    }

    printf("Informe o Código da Cidade (1-4):\n");
    scanf("%d", &codigoCidade);

    // Verificação do código da cidade
    if (codigoCidade < 1 || codigoCidade > 4) {
        printf("Erro: Código da cidade inválido.\n");
        return;
    }

    printf("Informe o Nome da Cidade:\n");
    scanf(" %[^\n]s", nomeCidade);

    // Verificação do nome da cidade
    if (nomeCidade == NULL || strlen(nomeCidade) == 0) {
        printf("Erro: Nome da cidade inválido.\n");
        return;
    }

    printf("Informe a UF da Cidade:\n");
    scanf("%s", uf);

    // Verificação da UF cidade
    if (uf == NULL || (strlen(uf) == 0 || strlen(uf) > 3)) {
        printf("Erro: UF inválida.\n");
        return;
    }

    printf("Código da Carta: %c%02d (%s-%s)\n", codigoEstado, codigoCidade, nomeCidade, uf);

    printf("Informe a População para %c%02d (%s-%s):\n", codigoEstado, codigoCidade, nomeCidade, uf);
    scanf("%lf", &populacao);

    // Verificação da população
    if (populacao < 0) {
        printf("Erro: População não pode ser negativa.\n");
        return;
    }

    printf("Informe a Área para %c%02d (%s-%s):\n", codigoEstado, codigoCidade, nomeCidade, uf);
    scanf("%lf", &area);

    // Verificação da área
    if (area <= 0) {
        printf("Erro: Área deve ser maior que zero.\n");
        return;
    }

    printf("Informe o PIB para %c%02d (%s-%s):\n", codigoEstado, codigoCidade, nomeCidade, uf);
    scanf("%lf", &pib);

    // Verificação do PIB
    if (pib < 0) {
        printf("Erro: PIB não pode ser negativo.\n");
        return;
    }

    printf("Informe a quantidade de Pontos Turísticos para %c%02d (%s-%s):\n", codigoEstado, codigoCidade, nomeCidade, uf);
    scanf("%d", &pontosTuristicos);

    // Verificação dos pontos turísticos
    if (pontosTuristicos < 0) {
        printf("Erro: Pontos turísticos não pode ser negativo.\n");
        return;
    }

    densidadePopulacional = calcDensidadePopulacional(populacao, area);
    pibPerCapita = calcPibPerCapita(pib, populacao);

    printf("***********************************\n");
    printf("   Carta cadastrada com sucesso!   \n");
    printf("***********************************\n");

    printf("Código da Carta: %c%02d\n", codigoEstado, codigoCidade);
    printf("Nome da cidade: %s - %s\n", nomeCidade, uf);
    printf("População: %.0lf\n", populacao);
    printf("Área: %.0lf km2\n", area);
    printf("PIB: %.2lf\n", pib);
    printf("Pontos Turísticos: %d\n", pontosTuristicos);
    printf("Densidade Populacional: %.0lf hab/km2\n", densidadePopulacional);
    printf("PIB per capita: %.2lf\n", pibPerCapita);
}

int main() {
    cadastrarCarta();
    return 0;
}
#include <stdio.h>
#include <string.h>
#include "CartasSuperTrunfo.h"

Carta cartas[MAX_CARTAS];
int totalCartas = 0;

int main() {
    int opcao;
    do {
        printf("\n1. Cadastrar Carta\n");
        printf("2. Comparar Cartas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCarta();
                break;
            case 2:
                compararCartas();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}

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

void cadastrarCarta() {
    if (totalCartas >= MAX_CARTAS) {
        printf("Erro: Número máximo de cartas atingido.\n");
        return;
    }

    Carta novaCarta;

    cabecalho();

    printf("Informe o Código do Estado (A-H):\n");
    scanf(" %c", &novaCarta.codigoEstado);

    if (novaCarta.codigoEstado < 'A' || novaCarta.codigoEstado > 'H') {
        printf("Erro: Código do estado inválido.\n");
        return;
    }

    printf("Informe o Código da Cidade (1-4):\n");
    scanf("%d", &novaCarta.codigoCidade);

    if (novaCarta.codigoCidade < 1 || novaCarta.codigoCidade > 4) {
        printf("Erro: Código da cidade inválido.\n");
        return;
    }

    printf("Informe o Nome da Cidade:\n");
    scanf(" %[^\n]s", novaCarta.nomeCidade);

    if (strlen(novaCarta.nomeCidade) == 0) {
        printf("Erro: Nome da cidade inválido.\n");
        return;
    }

    printf("Informe a UF da Cidade:\n");
    scanf("%s", novaCarta.uf);

    if (strlen(novaCarta.uf) == 0 || strlen(novaCarta.uf) > 3) {
        printf("Erro: UF inválida.\n");
        return;
    }

    printf("Informe a População para %c%02d (%s-%s):\n", novaCarta.codigoEstado, novaCarta.codigoCidade, novaCarta.nomeCidade, novaCarta.uf);
    scanf("%lu", &novaCarta.populacao);

    if (novaCarta.populacao < 0) {
        printf("Erro: População não pode ser negativa.\n");
        return;
    }

    printf("Informe a Área (km²) para %c%02d (%s-%s):\n", novaCarta.codigoEstado, novaCarta.codigoCidade, novaCarta.nomeCidade, novaCarta.uf);
    scanf("%lf", &novaCarta.area);

    if (novaCarta.area <= 0) {
        printf("Erro: Área deve ser maior que zero.\n");
        return;
    }

    printf("Informe o PIB para %c%02d (%s-%s):\n", novaCarta.codigoEstado, novaCarta.codigoCidade, novaCarta.nomeCidade, novaCarta.uf);
    scanf("%lf", &novaCarta.pib);

    if (novaCarta.pib < 0) {
        printf("Erro: PIB não pode ser negativo.\n");
        return;
    }

    printf("Informe a quantidade de Pontos Turísticos para %c%02d (%s-%s):\n", novaCarta.codigoEstado, novaCarta.codigoCidade, novaCarta.nomeCidade, novaCarta.uf);
    scanf("%d", &novaCarta.pontosTuristicos);

    if (novaCarta.pontosTuristicos < 0) {
        printf("Erro: Pontos turísticos não pode ser negativo.\n");
        return;
    }

    novaCarta.densidadePopulacional = calcDensidadePopulacional(novaCarta.populacao, novaCarta.area);
    novaCarta.pibPerCapita = calcPibPerCapita(novaCarta.pib, novaCarta.populacao);
    novaCarta.superPoder = calcularSuperPoder(novaCarta); // Calcula o Super Poder

    cartas[totalCartas++] = novaCarta;

    printf("***********************************\n");
    printf("   Carta cadastrada com sucesso!   \n");
    printf("***********************************\n");

    gerarCodigoCarta(novaCarta.codigoEstado, novaCarta.codigoCidade, novaCarta.nomeCidade, novaCarta.uf);
    printf("Nome da cidade: %s - %s\n", novaCarta.nomeCidade, novaCarta.uf);
    printf("População: %.0lu\n", novaCarta.populacao);
    printf("Área: %.0lf km2\n", novaCarta.area);
    printf("PIB: %.2lf\n", novaCarta.pib);
    printf("Número de Pontos Turísticos: %d\n", novaCarta.pontosTuristicos);
    printf("Densidade populacional: %.2f hab/km²\n", novaCarta.densidadePopulacional);
    printf("PIB per capita: %.6f reais\n", novaCarta.pibPerCapita);
    printf("Super Poder: %.2f\n", novaCarta.superPoder); // Exibe o Super Poder
}

void gerarCodigoCarta(char codigoEstado, int codigoCidade, char nomeCidade[100], char uf[3]) {
    printf("Código da Carta: %c%02d (%s-%s)\n", codigoEstado, codigoCidade, nomeCidade, uf);
}

double calcDensidadePopulacional(unsigned long int populacao, double area) {
    if (area == 0) {
        printf("Erro: Área não pode ser zero.\n");
        return 0;
    }
    return (populacao / area);
}

double calcPibPerCapita(double pib, unsigned long int populacao) {
    if (populacao == 0) {
        printf("Erro: População não pode ser zero.\n");
        return 0;
    }
    return (pib / populacao);
}

float calcularSuperPoder(Carta carta) {
    // Soma todos os atributos numéricos, incluindo o inverso da densidade populacional
    return (float)(carta.populacao + carta.area + carta.pib + carta.pontosTuristicos + carta.pibPerCapita + (1.0 / carta.densidadePopulacional));
}

void compararCartas() {
    if (totalCartas < 2) {
        printf("Erro: É necessário cadastrar pelo menos duas cartas para comparar.\n");
        return;
    }

    int carta1, carta2;
    printf("Escolha duas cartas para comparar (1 a %d):\n", totalCartas);
    scanf("%d %d", &carta1, &carta2);

    if (carta1 < 1 || carta1 > totalCartas || carta2 < 1 || carta2 > totalCartas) {
        printf("Erro: Escolha inválida.\n");
        return;
    }

    carta1--;
    carta2--;

    // Gerar os códigos das cartas
    char codigoCarta1[6], codigoCarta2[6];
    sprintf(codigoCarta1, "%c%02d", cartas[carta1].codigoEstado, cartas[carta1].codigoCidade);
    sprintf(codigoCarta2, "%c%02d", cartas[carta2].codigoEstado, cartas[carta2].codigoCidade);

    printf("\nComparação de Cartas:\n");

    // Comparação de população
    printf("População: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].populacao > cartas[carta2].populacao) ? 1 : 2, 
           (cartas[carta1].populacao > cartas[carta2].populacao) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].populacao > cartas[carta2].populacao) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].populacao > cartas[carta2].populacao) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].populacao > cartas[carta2].populacao) ? 1 : 0);

    // Comparação de área
    printf("Área: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].area > cartas[carta2].area) ? 1 : 2, 
           (cartas[carta1].area > cartas[carta2].area) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].area > cartas[carta2].area) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].area > cartas[carta2].area) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].area > cartas[carta2].area) ? 1 : 0);

    // Comparação de PIB
    printf("PIB: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].pib > cartas[carta2].pib) ? 1 : 2, 
           (cartas[carta1].pib > cartas[carta2].pib) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].pib > cartas[carta2].pib) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].pib > cartas[carta2].pib) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].pib > cartas[carta2].pib) ? 1 : 0);

    // Comparação de pontos turísticos
    printf("Pontos Turísticos: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos) ? 1 : 2, 
           (cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos) ? 1 : 0);

    // Comparação de densidade populacional (menor valor vence)
    printf("Densidade Populacional: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].densidadePopulacional < cartas[carta2].densidadePopulacional) ? 1 : 2, 
           (cartas[carta1].densidadePopulacional < cartas[carta2].densidadePopulacional) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].densidadePopulacional < cartas[carta2].densidadePopulacional) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].densidadePopulacional < cartas[carta2].densidadePopulacional) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].densidadePopulacional < cartas[carta2].densidadePopulacional) ? 1 : 0);

    // Comparação de PIB per capita
    printf("PIB per Capita: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].pibPerCapita > cartas[carta2].pibPerCapita) ? 1 : 2, 
           (cartas[carta1].pibPerCapita > cartas[carta2].pibPerCapita) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].pibPerCapita > cartas[carta2].pibPerCapita) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].pibPerCapita > cartas[carta2].pibPerCapita) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].pibPerCapita > cartas[carta2].pibPerCapita) ? 1 : 0);

    // Comparação de Super Poder
    printf("Super Poder: Carta %d (%s - %s - %s) venceu (%d)\n", 
           (cartas[carta1].superPoder > cartas[carta2].superPoder) ? 1 : 2, 
           (cartas[carta1].superPoder > cartas[carta2].superPoder) ? codigoCarta1 : codigoCarta2, 
           (cartas[carta1].superPoder > cartas[carta2].superPoder) ? cartas[carta1].nomeCidade : cartas[carta2].nomeCidade, 
           (cartas[carta1].superPoder > cartas[carta2].superPoder) ? cartas[carta1].uf : cartas[carta2].uf, 
           (cartas[carta1].superPoder > cartas[carta2].superPoder) ? 1 : 0);
}
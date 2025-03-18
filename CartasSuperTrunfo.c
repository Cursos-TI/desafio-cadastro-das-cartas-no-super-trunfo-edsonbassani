#include <stdio.h>
#include <string.h>
#include "CartasSuperTrunfo.h"

Carta cartas[MAX_CARTAS];
int totalCartas = 0;

int main() {
    //Menu Principal
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
    Carta novaCarta;
    
    if (totalCartas >= MAX_CARTAS) {
        printf("Erro: Número máximo de cartas atingido.\n");
        return;
    }

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

    // Menu de atributos
    int atributo1, atributo2;
    int atributosDisponiveis[6] = {1, 2, 3, 4, 5, 6}; // 1: População, 2: Área, 3: PIB, 4: Pontos Turísticos, 5: Densidade Populacional, 6: PIB per Capita

    printf("Escolha o primeiro atributo para comparação:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("6. PIB per Capita\n");
    scanf("%d", &atributo1);

    if (atributo1 < 1 || atributo1 > 6) {
        printf("Erro: Atributo inválido.\n");
        return;
    }

    // Remover o atributo escolhido das opções disponíveis
    atributosDisponiveis[atributo1 - 1] = 0;

    printf("Escolha o segundo atributo para comparação:\n");
    for (int i = 0; i < 6; i++) {
        if (atributosDisponiveis[i] != 0) {
            printf("%d. %s\n", atributosDisponiveis[i], 
                   atributosDisponiveis[i] == 1 ? "População" :
                   atributosDisponiveis[i] == 2 ? "Área" :
                   atributosDisponiveis[i] == 3 ? "PIB" :
                   atributosDisponiveis[i] == 4 ? "Pontos Turísticos" :
                   atributosDisponiveis[i] == 5 ? "Densidade Populacional" : "PIB per Capita");
        }
    }
    scanf("%d", &atributo2);

    if (atributo2 < 1 || atributo2 > 6 || atributosDisponiveis[atributo2 - 1] == 0) {
        printf("Erro: Atributo inválido ou já escolhido.\n");
        return;
    }

    // Comparação dos atributos
    double valorAtributo1Carta1, valorAtributo1Carta2;
    double valorAtributo2Carta1, valorAtributo2Carta2;

    switch (atributo1) {
        case 1:
            valorAtributo1Carta1 = cartas[carta1].populacao;
            valorAtributo1Carta2 = cartas[carta2].populacao;
            break;
        case 2:
            valorAtributo1Carta1 = cartas[carta1].area;
            valorAtributo1Carta2 = cartas[carta2].area;
            break;
        case 3:
            valorAtributo1Carta1 = cartas[carta1].pib;
            valorAtributo1Carta2 = cartas[carta2].pib;
            break;
        case 4:
            valorAtributo1Carta1 = cartas[carta1].pontosTuristicos;
            valorAtributo1Carta2 = cartas[carta2].pontosTuristicos;
            break;
        case 5:
            valorAtributo1Carta1 = cartas[carta1].densidadePopulacional;
            valorAtributo1Carta2 = cartas[carta2].densidadePopulacional;
            break;
        case 6:
            valorAtributo1Carta1 = cartas[carta1].pibPerCapita;
            valorAtributo1Carta2 = cartas[carta2].pibPerCapita;
            break;
    }

    switch (atributo2) {
        case 1:
            valorAtributo2Carta1 = cartas[carta1].populacao;
            valorAtributo2Carta2 = cartas[carta2].populacao;
            break;
        case 2:
            valorAtributo2Carta1 = cartas[carta1].area;
            valorAtributo2Carta2 = cartas[carta2].area;
            break;
        case 3:
            valorAtributo2Carta1 = cartas[carta1].pib;
            valorAtributo2Carta2 = cartas[carta2].pib;
            break;
        case 4:
            valorAtributo2Carta1 = cartas[carta1].pontosTuristicos;
            valorAtributo2Carta2 = cartas[carta2].pontosTuristicos;
            break;
        case 5:
            valorAtributo2Carta1 = cartas[carta1].densidadePopulacional;
            valorAtributo2Carta2 = cartas[carta2].densidadePopulacional;
            break;
        case 6:
            valorAtributo2Carta1 = cartas[carta1].pibPerCapita;
            valorAtributo2Carta2 = cartas[carta2].pibPerCapita;
            break;
    }

    // Determinar o vencedor de cada atributo
    int vencedorAtributo1, vencedorAtributo2;
    if (atributo1 == 5) {
        // Densidade Populacional: menor valor vence
        vencedorAtributo1 = (valorAtributo1Carta1 < valorAtributo1Carta2) ? 1 : 2;
    } else {
        vencedorAtributo1 = (valorAtributo1Carta1 > valorAtributo1Carta2) ? 1 : 2;
    }

    if (atributo2 == 5) {
        // Densidade Populacional: menor valor vence
        vencedorAtributo2 = (valorAtributo2Carta1 < valorAtributo2Carta2) ? 1 : 2;
    } else {
        vencedorAtributo2 = (valorAtributo2Carta1 > valorAtributo2Carta2) ? 1 : 2;
    }

    // Soma dos atributos
    double somaCarta1 = valorAtributo1Carta1 + valorAtributo2Carta1;
    double somaCarta2 = valorAtributo1Carta2 + valorAtributo2Carta2;

    // Determinar o vencedor final
    int vencedorFinal;
    if (somaCarta1 > somaCarta2) {
        vencedorFinal = 1;
    } else if (somaCarta2 > somaCarta1) {
        vencedorFinal = 2;
    } else {
        vencedorFinal = 0; // Empate
    }

    // Exibir resultados
    printf("\nResultado da Comparação:\n");
    printf("Carta 1: %s - %s\n", cartas[carta1].nomeCidade, cartas[carta1].uf);
    printf("Carta 2: %s - %s\n", cartas[carta2].nomeCidade, cartas[carta2].uf);

    printf("\nAtributo 1: ");
    switch (atributo1) {
        case 1: printf("População\n"); break;
        case 2: printf("Área\n"); break;
        case 3: printf("PIB\n"); break;
        case 4: printf("Pontos Turísticos\n"); break;
        case 5: printf("Densidade Populacional\n"); break;
        case 6: printf("PIB per Capita\n"); break;
    }
    printf("Carta 1: %.2f\n", valorAtributo1Carta1);
    printf("Carta 2: %.2f\n", valorAtributo1Carta2);
    printf("Vencedor do Atributo 1: Carta %d\n", vencedorAtributo1);

    printf("\nAtributo 2: ");
    switch (atributo2) {
        case 1: printf("População\n"); break;
        case 2: printf("Área\n"); break;
        case 3: printf("PIB\n"); break;
        case 4: printf("Pontos Turísticos\n"); break;
        case 5: printf("Densidade Populacional\n"); break;
        case 6: printf("PIB per Capita\n"); break;
    }
    printf("Carta 1: %.2f\n", valorAtributo2Carta1);
    printf("Carta 2: %.2f\n", valorAtributo2Carta2);
    printf("Vencedor do Atributo 2: Carta %d\n", vencedorAtributo2);

    printf("\nSoma dos Atributos:\n");
    printf("Carta 1: %.2f\n", somaCarta1);
    printf("Carta 2: %.2f\n", somaCarta2);

    if (vencedorFinal == 0) {
        printf("\nEmpate!\n");
    } else {
        printf("\nVencedor Final: Carta %d\n", vencedorFinal);
    }
}

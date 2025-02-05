#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.


// Sugestão: Defina variáveis separadas para cada atributo da cidade.
// Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    
// Cadastro das Cartas:
// Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
// Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    
// Exibição dos Dados das Cartas:
// Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
// Exiba os valores inseridos para cada atributo da cidade, um por linha.


int main() {

    char codigoEstado;
    int codigoCidade;
    double populacao;
    double area;
    double pib;
    int pontosTuristicos;


    printf("***********************************\n");
    printf("************ MateCheck ************\n");
    printf("***********************************\n");
    printf("****** Super Trunfo - Países ******\n");
    printf("***********************************\n");
    printf("************* Bem-vindo ***********\n");
    printf("***********************************\n");
    printf("******* Cadastro de Cartas ********\n");
    printf("***********************************\n");

    printf("Carta #1: \n");

    printf("Informe o Código do Estado (A-H):\n");
    scanf(" %c", &codigoEstado);

    printf("Informe o Código da Cidade (1-4):\n");
    scanf("%d", &codigoCidade);

    printf("Informe a População para %c-%02d:\n", codigoEstado, codigoCidade);
    scanf("%lf", &populacao);

    printf("Informe a Área para %c-%02d:\n", codigoEstado, codigoCidade);
    scanf("%lf", &area);

    printf("Informe o PIB para %c-%02d:\n", codigoEstado, codigoCidade);
    scanf("%lf", &pib);

    printf("Informe a quantidade de Pontos Turisticos para %c-%02d:\n", codigoEstado, codigoCidade);
    scanf("%d", &pontosTuristicos);

    printf("***********************************\n");
    printf("    Carta cadastrada com sucesso!  \n");
    printf("***********************************\n");

    printf("Código: %c-%02d\n", codigoEstado, codigoCidade);
    printf("População: %.2lf\n", populacao);
    printf("Área: %.2lf\n", area);
    printf("PIB: %.2lf\n", pib);
    printf("Pontos Turísticos: %d\n", pontosTuristicos);

    return 0;
}

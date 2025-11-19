#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes
#define TAMANHO 5
#define NAVIOS 5
#define AGUA '~'
#define NAVIO 'N'
#define ERRO 'E'
#define ACERTO 'A'

// Imprime o tabuleiro do jogo
void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    printf("   ");
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        // printf("%d  ", i);
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("%c  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Imprime o tabuleiro personalizado
void imprimirTabuleiroEmoji(char tabuleiro[TAMANHO][TAMANHO])
{
    printf("   ");
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++)
        {
            if (tabuleiro[i][j] == AGUA)
            {
                printf("🌊 ");
            }
            else if (tabuleiro[i][j] == ACERTO)
            {
                printf("💥 ");
            }
            else if (tabuleiro[i][j] == ERRO)
            {
                printf("⭕ ");
            }
            else
            {
                printf("🚢 ");
            }
        }
        printf("\n");
    }
}

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void posicionarNaviosAleatorios(char tabuleiro[TAMANHO][TAMANHO], int numNavios)
{
    int x, y;
    for (int i = 0; i < numNavios; i++)
    {
        do
        {
            x = rand() % TAMANHO;
            y = rand() % TAMANHO;
        } while (tabuleiro[x][y] == NAVIO);
        tabuleiro[x][y] = NAVIO;
        
    }
}

int ataqueComputador(char tabuleiro[TAMANHO][TAMANHO], int acertos, int cpu)
{
    int linha, coluna;

    do
    {
        linha = 'A' + rand() % TAMANHO;
        coluna = rand() % TAMANHO;
    } while (tabuleiro[linha - 'A'][coluna] == 'E' || tabuleiro[linha - 'A'][coluna] == 'A');

    if (tabuleiro[linha - 'A'][coluna] == NAVIO)
    {
        printf("Computador %d acertou em %c %d!\n", cpu, linha, coluna + 1);
        tabuleiro[linha - 'A'][coluna] = ACERTO;
        acertos++;
    }
    else
    {
        printf("Computador %d errou em %c %d!\n", cpu, linha, coluna + 1);
        tabuleiro[linha - 'A'][coluna] = ERRO;
    }

    return acertos;
}

int main()
{
    char tabuleiroComputador1[TAMANHO][TAMANHO];
    char tabuleiroComputador2[TAMANHO][TAMANHO];
    int acertosComputador1 = 0, acertosComputador2 = 0;

    srand(time(NULL));

    inicializarTabuleiro(tabuleiroComputador1);
    inicializarTabuleiro(tabuleiroComputador2);

    posicionarNaviosAleatorios(tabuleiroComputador1, NAVIOS);
    posicionarNaviosAleatorios(tabuleiroComputador2, NAVIOS);

    while (1)
    {
        printf("Tabuleiro do Computador 1:\n");
        imprimirTabuleiroEmoji(tabuleiroComputador1);
        printf("\n");
        printf("Tabuleiro do Computador 2:\n");
        imprimirTabuleiroEmoji(tabuleiroComputador2);

        acertosComputador1 = ataqueComputador(tabuleiroComputador2, acertosComputador1, 1);

        if (acertosComputador1 == NAVIOS)
        {
            printf("Computador 1 venceu! 🎆\n");
            imprimirTabuleiroEmoji(tabuleiroComputador2);
            break;
        }

        acertosComputador2 = ataqueComputador(tabuleiroComputador1, acertosComputador2, 2);

        if (acertosComputador2 == NAVIOS)
        {
            printf("Computador 2 venceu! 🎆\n");
            imprimirTabuleiroEmoji(tabuleiroComputador1);
            break;
        }

        getchar();
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 8
#define NAVIOS 5
#define TENTATIVAS 25

void inicializarTabuleiro(int tab[TAM][TAM]) {
    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

void exibirTabuleiroJogador(int tab[TAM][TAM]) {
    printf("\n    ");
    for(int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");
    for(int i = 0; i < TAM; i++) {
        printf("%d | ", i);
        for(int j = 0; j < TAM; j++) {
            if(tab[i][j] == 2) printf("X ");
            else if(tab[i][j] == 3) printf("O ");
            else printf("~ ");
        }
        printf("\n");
    }
}

void exibirTabuleiroCompleto(int tab[TAM][TAM]) {
    printf("\nTABULEIRO COMPLETO (DEBUG / FINAL)\n    ");
    for(int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for(int i = 0; i < TAM; i++) {
        printf("%d | ", i);
        for(int j = 0; j < TAM; j++) {
            if(tab[i][j] == 1) printf("N ");
            else if(tab[i][j] == 2) printf("X ");
            else if(tab[i][j] == 3) printf("O ");
            else printf("~ ");
        }
        printf("\n");
    }
}

void posicionarNavios(int tab[TAM][TAM]) {
    int colocados = 0;
    while(colocados < NAVIOS) {
        int l = rand() % TAM;
        int c = rand() % TAM;
        if(tab[l][c] == 0) {
            tab[l][c] = 1;
            colocados++;
        }
    }
}

int verificarTiro(int tab[TAM][TAM], int l, int c) {
    if(tab[l][c] == 1) { tab[l][c] = 2; return 1; }
    if(tab[l][c] == 0) { tab[l][c] = 3; return 0; }
    return -1;
}

int main() {
    int tab[TAM][TAM];
    int acertos = 0, linha, coluna;

    srand(time(NULL));
    inicializarTabuleiro(tab);
    posicionarNavios(tab);

    printf("===== BATALHA NAVAL COMPLETA =====\n");

    for(int t = 1; t <= TENTATIVAS; t++) {
        exibirTabuleiroJogador(tab);
        printf("\nTentativa %d de %d\n", t, TENTATIVAS);

        printf("Linha (0-%d): ", TAM-1);
        scanf("%d", &linha);
        printf("Coluna (0-%d): ", TAM-1);
        scanf("%d", &coluna);

        if(linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Coordenadas inválidas!\n");
            continue;
        }

        int r = verificarTiro(tab, linha, coluna);

        if(r == 1) {
            acertos++;
            printf("🎯 ACERTOU um navio!\n");
        }
        else if(r == 0) {
            printf("❌ Água!\n");
        }
        else {
            printf("Você já atirou aí!\n");
            continue;
        }

        if(acertos == NAVIOS) {
            printf("\n🔥 Você destruiu todos os navios!\n");
            break;
        }
    }

    printf("\n===== FIM DE JOGO =====\n");
    exibirTabuleiroCompleto(tab);

    return 0;
}

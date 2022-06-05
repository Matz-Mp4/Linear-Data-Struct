
#include "Booleano.h"
#include <stdio.h>

#define Max 10
#define fantasma 0
#define sinal -1

typedef struct Fila{
    int inicio;               // mostra onde esta o primeiro elemento
    int fim;                  // mostra onde esta o ultimo elemento
    unsigned char Vetor[Max]; // onde sao armazenados os inteiros positivos
} Fila;

Fila criarFila();
bool filaVazia(Fila);
bool filaCheia(Fila);
unsigned char acessarPrimeiro(Fila);
Fila pushFila(Fila, unsigned char);
Fila popFila(Fila);
Fila esvaziarFila();
void mostrarFila(Fila);
Fila pushFilaaArq(char *palavra, Fila A);

Fila pushFilaArq(char *palavra, Fila A){
     
     FILE *arq = fopen(palavra, "rt");
     int elemento;
     int tem = A.inicio;
     
     
         while(! feof(arq)){
            elemento = (int)fgetc(arq);
            A = pushFila(A, elemento);
        }
     

    return A;
}

Fila esvaziarFila(){

    Fila S;
    S.inicio = sinal;
    S.fim = sinal;
    return S;
}

Fila criarFila(){

    Fila S;
    S.inicio = sinal;
    S.fim = sinal;
    return S;
}

bool filaVazia(Fila S){

    bool vazia = FALSE;
    
    if (S.inicio == sinal)
        vazia = TRUE;
    
    return vazia;
}

bool filaCheia(Fila S){

    bool cheio = FALSE;
    
    int k = (S.fim + 1) % Max;
    
    if(k == S.inicio){
        cheio = TRUE;
    }
}

unsigned char acessarPrimeiro(Fila S){
    int  p;
    unsigned char f;

    if (S.inicio == sinal)
        f = fantasma;
    else{
        p = S.inicio;
        f = S.Vetor[p];
    }
    return f;
}

Fila pushFila(Fila S, unsigned char y)
{
    int seg;

    seg = (S.fim + 1) % Max;

    if (seg != S.inicio){
        S.Vetor[seg] = y;
        if (S.inicio == sinal)
            S.inicio = seg;
        S.fim = seg;
    }
    return S;
}

void mostrarFila(Fila S){

    int k;
    int fim = (S.fim + 1) % Max;

    if (S.inicio != sinal){
        k = S.inicio;
     

        while (k != fim){

            printf("%c", S.Vetor[k]);
            k = (k + 1) % Max;
        }
    }
    else{
        printf("\nFila Vazia");
    }
}

Fila popFila(Fila S){
    
    int seg;

    if(S.inicio != sinal) {

        //Se a fila tem um unico elemento,
         
        if(S.inicio == S.fim) {

            S.inicio = sinal;
            S.fim = sinal;
        } else {
            seg = (S.inicio + 1) % Max;
            S.inicio = seg;
        }    
    }
    return S;
}
#define fantasma 36
#define Max 10
#define sinal -1 

#include "Booleano.h"
#include <stdio.h>

typedef struct Pilha{	
    int topo;                  //armazena a posicao do ultimo elemento da pilha
    unsigned char Vetor[Max];  //armazena os elementos da pilha

}Pilha;

//interface
Pilha criarPilha();
bool pilhaVazia(Pilha);
bool pilhaCheia(Pilha);
Pilha pushPilha(Pilha , unsigned char);
Pilha popPilha(Pilha);
unsigned char acessarTopo(Pilha);
Pilha esvaziarPilha(Pilha);
void mostrarPilha(Pilha);
Pilha pushPilhaArq(char *, Pilha );

Pilha criarPilha(){

    Pilha S;
    S.topo = sinal;

    return S;
}

Pilha pushPilhaArq(char *palavra, Pilha A){
     
     FILE *arq = fopen(palavra, "rt");
     int elemento;

     if(A.topo != Max - 1) {
     
         while(! feof(arq)){
            elemento = fgetc(arq);
            A = pushPilha(A, elemento);
        }
     }

    return A;
}

bool pilhaVazia(Pilha S){
	
	bool veri = FALSE;
	
	if(S.topo == sinal){
		veri = TRUE;
	}
	
	return veri;
}
unsigned char acessarTopo(Pilha S){
	
	unsigned char y;
	int p;
	
	if(S.topo != sinal){
		p = S.topo;
		y = S.Vetor[p];
	}else{
		y = fantasma;
	}
	
	return y;
}
bool PilhaCheia(Pilha  S){
	
	bool veri = FALSE;
	if(S.topo == Max - 1){
		veri = TRUE;
	}
	
	return veri;
}

void mostrarPilha(Pilha S){
    
    int k, t;
    t = S.topo;
    
    if(t == sinal)
        printf("\n Pilha vazia.");
    else{
        for(k = t; k >= 0; k--)
        {
            printf(" %c\n", S.Vetor[k]);
        }
    }
}


Pilha pushPilha(Pilha  S, unsigned char ch){
	
	if(S.topo != Max - 1){
		S.topo = S.topo + 1;
		S.Vetor[S.topo] = ch;		
	}
	
	return S;
}

 
Pilha popPilha(Pilha  S){
	
	if(S.topo != sinal){
		S.topo = S.topo - 1;
	}
	
	return S;
}



#ifndef _Dicionario_h
#define _Dicionario_h

#include "ListaLigada.h"
#include <ctype.h>

#define sinal -1

typedef struct Dicionario {

  Lista bloco[26];
  int tam;
} Dicionario;

const char *alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

Dicionario criarDic();
int buscar(Dicionario, char *);
void mostrar(Dicionario);
Dicionario remover(Dicionario, char *);
Dicionario inserir(Dicionario, char *);

Dicionario criarDic() {
  Dicionario A;
  A.tam = 0;
  int i;
  for (i = 0; i < 26; i++) {
    A.bloco[i] = criarLista(alfabeto[i]);
  }

  return A;
}

void mostrar(Dicionario A) {

  int i;
  if (A.tam == 0)
    printf("\nDicionario vazio!");
  else {
    for (i = 0; i < 26; i++) {
      printf("\n Nomes com a letra : %c =>", A.bloco[i].letra);
      mostrarLista(A.bloco[i]);
    }
  }
}

int buscar(Dicionario A, char *nome) {
  int i = 0, posicao = sinal;
  char letra;
  bool achou = false;

    letra = toupper(nome[0]);

    while (achou == false && i < 26) {
      if (letra == A.bloco[i].letra) {
        achou = true;
        posicao = i;
      }
      i++;
    }

  return posicao;
}

Dicionario inserir(Dicionario A, char *nome) {

  int pos = buscar(A, nome);
  bool veri = false;
  if (pos != sinal) {
    veri = inserirLista(&A.bloco[pos], nome);
    if (veri == true) {
      A.tam++;
    }
  }

  return A;
}

Dicionario remover(Dicionario A, char *nome) {
  bool veri = false;
  int pos;
  if (A.tam != 0) {
    pos = buscar(A, nome);
    veri = removerLista(&A.bloco[pos], nome);
    if (veri == true) {
      A.tam--;
    }
  }
  return A;
}


#endif

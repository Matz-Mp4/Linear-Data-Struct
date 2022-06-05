#ifndef _Fila_h #define _Fila_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
  unsigned char item;
  struct Celula *next;
} Celula;

typedef struct Fila {
  Celula *inicio;
  Celula *fim;
} Fila;

Fila criarFila();
bool filaVazia();
void mostrarFila(Fila);
Fila pushFila(Fila, unsigned char);
Fila popFila(Fila);

Fila criarFila() {
  Fila A;
  A.inicio = NULL;
  A.fim = NULL;

  return A;
}

bool filaVazia(Fila A) {
  bool veri = false;

  if (A.inicio == NULL) {
    veri = true;
  }
  return veri;
}

void mostrarFila(Fila A) {
  Celula *apont;

  if (A.inicio == NULL) {
    printf("\n Fila vazia");
  } else {
    printf("\nFila: ");
    apont = A.inicio;
    do {
      printf("%c ", apont->item);
      apont = apont->next;
    } while (apont != NULL);
  }
}

Fila pushFila(Fila A, unsigned char item) {

  Celula *novo = (Celula *)malloc(sizeof(Celula));
  Celula *cel;
  novo->item = item;
  novo->next = NULL;

  if (A.inicio == NULL) {
    A.fim = novo;
    A.inicio = novo;
  } else {
    cel = A.fim;
    cel->next = novo;
  }
  A.fim = novo;

  return A;
}

Fila popFila(Fila A) {
  Celula *apont;
  if (A.inicio != NULL) {
    apont = A.inicio;
    A.inicio = apont->next;

    if (A.fim == apont) {
      A.fim = NULL;
    }
    free(apont);
  }
  return A;
}
#endif

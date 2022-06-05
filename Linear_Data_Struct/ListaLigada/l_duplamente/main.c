#include "ListaLigada.h"
#include <stdio.h>

int main() {
  Lista A = criarLista();
  Lista B = criarLista();
  Lista comple = criarLista();

  
  A = inserirFim(A, 2);
  A = inserirFim(A, 1);
  A = inserirFim(A, 1);
  A = inserirFim(A, 1);
  A = inserirFim(A, 3);
  mostraLista(A);

  A = removerDuplicata(A, 1);

  mostraLista(A);
  printf("\n");
  return 0;
}

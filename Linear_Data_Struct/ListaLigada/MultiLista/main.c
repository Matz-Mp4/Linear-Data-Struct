#include "Dicionario.h"

int main() {
  Dicionario A = criarDic();
  A = inserir(A, "Lucas");
  A = inserir(A, "Luara");
  A = inserir(A, "Luana");
  A = inserir(A, "Mateus");
  A = inserir(A, "Lucas");
  A = inserir(A, "Guilherme");
  mostrar(A);
  printf("\n\n\n");
  return 0;
}

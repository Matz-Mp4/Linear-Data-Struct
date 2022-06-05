#ifndef _Pilha_h
#define _Pilha_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ghost 36

typedef struct Celula {
  char item;
  struct Celula *next;
} Celula;

typedef Celula *Pilha;

Pilha criarPilha();
Pilha pushPilha(Pilha, unsigned char);
Pilha popPilha(Pilha);
char acessarTopo(Pilha);
void mostrarPilha(Pilha);
bool pilhaVazia(Pilha);
Pilha inverterFrase(char *);

/*
     @parm nenhum
     @return uma variavel do tipo Pilha
     @function cria uma Pilha vazia
*/
Pilha criarPilha() {
  Pilha A = NULL;
  return A;
}

/*
    @parm uma variavel do tipo Pilha, uma variavel unsigned char
    @return uma variavel do tipo Pilha
    @function adiciona um novo elemento na Pilha
*/
Pilha pushPilha(Pilha A, unsigned char item) {
  Celula *apont, *novo;

  novo = (Celula *)malloc(sizeof(Celula));
  novo->item = item;
  if (A == NULL) {
    novo->next = NULL;
  } else {
    novo->next = A;
  }
  A = novo;

  return A;
}

/*
    @parm uma variavel do tipo Pilha
    @return uma variavel do tipo Pilha
    @function remove o elemento do  topo da Pilha
*/
Pilha popPilha(Pilha A) {

  Celula *remove;
  if (A != NULL) {
    remove = A;
    A = remove->next;
    free(remove);
  }
  return A;
}

/*
    @parm uma variavel do tipo Pilha
    @return uma variavel unsigned char
    @function acessar o elemento no topo da Pilha
*/

char acessarTopo(Pilha A) {
  char item = ghost;
  Celula *apont;
  if (A != NULL) {
    apont = A;
    item = apont->item;
  }
  return item;
}

/*
    @parm uma variavel do tipo Lista
    @return nenhum
    @function mostra os elementos da pilha a partir do topo
*/
void mostrarPilha(Pilha A) {
  Celula *cel;

  if (A == NULL) {
    printf("Pilha vazia");
  } else {
    cel = A;
    printf("\n/----Pilha----\\");
    do {

      printf("\n %c", cel->item);
      cel = cel->next;
    } while (cel != NULL);
  }
}

bool pilhaVazia(Pilha A) {
  bool veri = false;

  if (A == NULL) {
    veri = true;
  }
  return veri;
}

/*
    @param um vetor do tipo char
    @return uma variavel do tipo Pilha
    @function inverte as palavras da frase e nao a frase em si

*/

Pilha inverterFrase(char palavra[]) {
  int tam = strlen(palavra);
  int i, j, inicio, fim;
  bool acheiInicio = false;
  Pilha invertido = criarPilha();

  for (i = 0; i < tam; i++) {
    if (palavra[i] != ' ' && acheiInicio == false) {
      inicio = i;
      acheiInicio = true;
    } else if ((palavra[i] == ' ' || i == tam - 1) && acheiInicio == true) {

      fim = i - 1;

      if (palavra[i] != ' ') {
        fim = i;
      }

      for (j = inicio; j <= fim; j++) {
        invertido = pushPilha(invertido, palavra[j]);
      }
      acheiInicio = false;
    } else if (palavra[i] == ' ') {
      invertido = pushPilha(invertido, ' ');
    }
  }

  return invertido;
}
#endif

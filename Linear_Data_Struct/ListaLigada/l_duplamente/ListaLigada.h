#ifndef _ListaLigada_h
#define _ListaLigada_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ghost -1

typedef struct Celula {
  int valor;
  struct Celula *pre;
  struct Celula *next;
} Celula;

typedef struct {
  int tam;
  Celula *inicio;
  Celula *fim;
} Lista;

Lista criarLista();
bool estaVazio(Lista);
Lista inserirInicio(Lista, int);
Lista inserirFim(Lista, int);
Lista inserirPosicao(Lista, int, int);
Lista inserirOrdenado(Lista, int);
Lista remover(Lista, int);
void mostraLista(Lista);
Lista obterInterseccao(Lista, Lista);
Lista inverter(Lista);
Lista obterComplementar(Lista, Lista);
Lista removerDuplicata(Lista, int);

/*
   @param nenhum
   @return uma variavel do tipo Lista
   @function cria uma lista vazia
*/
Lista criarLista() {
  Lista A;
  A.inicio = NULL;
  A.fim = NULL;
  A.tam = 0;
  return A;
}

/*
    @parm uma variavel do tipo Lista
    @return uma variavel do tipo bool
    @function verifica se a lista esta vazia
*/

bool estaVazio(Lista A) {
  bool veri = false;

  if (A.tam == 0) {
    veri = true;
  }
  return veri;
}

/*
    @parm uma variavel do tipo Lista, uma variavel int
    @return uma variavel do tipo Lista
    @function insere um novo elemento no inicio da lista
*/
Lista inserirInicio(Lista A, int item) {
  Celula *novo = (Celula *)malloc(sizeof(Celula));
  Celula *prox;

  if (novo != NULL) {
    novo->next = A.inicio;
    novo->valor = item;
    novo->pre = NULL;
    A.inicio = novo;

    if (A.tam == 0) {
      A.fim = novo;
    } else {
      prox = novo->next;
      prox->pre = novo;
    }
    A.tam++;
  }
  return A;
}

/*
    @parm uma variavel do tipo Lista, uma variavel int
    @return uma variavel do tipo Lista
    @function insere um novo elemento no fim da lista
*/

Lista inserirFim(Lista A, int item) {
  Celula *novo = (Celula *)malloc(sizeof(Celula));
  Celula *ant;

  if (novo != NULL) {
    novo->valor = item;
    novo->next = NULL;
    novo->pre = A.fim;
    A.fim = novo;
    if (A.inicio == NULL) {
      A.inicio = novo;
    } else {
      ant = novo->pre;
      ant->next = novo;
    }

    A.tam++;
  }
  return A;
}

/*
    @param uma variavel do tipo Lista, uma variavel int, uma variavel do tipo
   int
    @return  uma varaivel do tipo Lista
    @function insere um novo elemento na frente da posicao fornecida
    1 parametro uma lista, 2 parametro o item, 3 parametro posicao
*/
Lista inserirPosicao(Lista A, int item, int posicao) {
  Celula *novo = (Celula *)malloc(sizeof(Celula));
  Celula *apont, *prox;
  int i;
  if (novo != NULL) {
    if (posicao >= 1 && posicao <= A.tam) {
      if (posicao == A.tam) {
        A = inserirFim(A, item);
      } else {
        apont = A.inicio;
        i = 1;
        while (i < posicao) {
          apont = apont->next;
          i++;
        }
        novo->valor = item;
        prox = apont->next;
        prox->pre = novo;
        novo->next = prox;
        novo->pre = apont;
        apont->next = novo;

        A.tam++;
      }
    } else if (A.tam == 0 && posicao == 1) {
      A = inserirInicio(A, item);
    }
  }
  return A;
}

/*
    @param uma variavel do tipo Lista, uma varaivel int
    @return uma varaivel do tipo Lista
    @function insere um elemento em ordem crescente se nao tiver duplicata
*/
Lista inserirOrdenado(Lista A, int item) {
  Celula *apont, *novo, *posicaoMaior, *ant;
  bool veri = false, temDuplicata = false;

  if (A.tam == 0) {
    novo = (Celula *)malloc(sizeof(Celula));
    A.inicio = novo;
    A.fim = novo;
    novo->valor = item;
    A.tam++;
  } else {
    apont = A.inicio;

    while (apont->next != NULL && item >= apont->valor) {
      if (item == apont->valor) {
        temDuplicata = true;
      }
      apont = apont->next;
    }

    novo = (Celula *)malloc(sizeof(Celula));
    novo->valor = item;

    if (temDuplicata == false) {
      novo = (Celula *)malloc(sizeof(Celula));
      novo->valor = item;

      if (apont == A.inicio) {
        novo->pre = NULL;
        novo->next = A.inicio;
        apont->pre = novo;
        A.inicio = novo;

      } else if (apont == A.fim && apont->valor < item) {
        apont->next = novo;
        A.fim = novo;
        novo->next = NULL;
        novo->pre = apont;

      } else {
        ant = apont->pre;
        novo->next = apont;
        novo->pre = ant;
        ant->next = novo;
        apont->pre = novo;
      }
    }
  }
  return A;
}

/*
    @param uma variavel do tipo Lista, uma variavel int
    @return uma variavel do tipo Lista
    @function remove o primeiro  elemento com um certo valor
*/
Lista remover(Lista A, int item) {
  Celula *apont, *prox, *ant;
  if (A.tam != 0) {
    apont = A.inicio;

    while (apont->next != NULL && apont->valor != item) {
      apont = apont->next;
    }
    if (apont->valor == item) {
      if (apont == A.inicio && apont != A.fim) {
        prox = apont->next;
        A.inicio = prox;
        prox->pre = NULL;
      } else if (apont == A.inicio && apont == A.fim) {
        A.inicio = NULL;
        A.fim = NULL;
      } else if (apont == A.fim) {
        ant = apont->pre;
        A.fim = ant;
        ant->next = NULL;
      } else {
        ant = apont->pre;
        prox = apont->next;

        ant->next = prox;
        prox->pre = ant;
      }
      A.tam--;
      free(apont);
    }
  }
  return A;
}
/*
    @param uma variavel do tipo Lista
    @return nenhum
    @function mostrar os elementos da lista
*/

void mostraLista(Lista A) {

  Celula *apont;

  if (A.tam == 0)
    printf("\nLista vazia");
  else {
    apont = A.inicio;
    printf("\n Lista:");
    do {
      printf(" %d", apont->valor);
      apont = apont->next;
    } while (apont != NULL);
  }
}

/*
    @param uma varaivel do tipo Lista, uma variavel do tipo Lista
    @return uma variavel do tipo Lista
    @function obtem os elementos que estao ao mesmo tempo nas duas lista
              as duas lista nao pode ter duplicata
*/

Lista obterInterseccao(Lista A, Lista B) {

  Celula *apontA, *apontB;
  int elemento;
  bool veri = false;
  Lista inter;

  if (A.tam != 0 && B.tam != 0) {
    apontA = A.inicio;
    Lista inter = criarLista();
    do {
      apontB = B.inicio;
      do {
        if (apontB->valor == apontA->valor) {
          veri = true;
          elemento = apontA->valor;
          inter = inserirFim(inter, elemento);
        }
        apontB = apontB->next;
      } while (apontB != NULL);

      apontA = apontA->next;
    } while (apontA != NULL);
  }

  return inter;
}

/*
    @param uma varaivel do tipo Lista
    @return uma varaivel do tipo Lista
    @function inverte uma lista
*/

Lista inverter(Lista A) {

  Celula *apont, *ant, *seg;
  if (A.tam > 1) {
    apont = A.inicio;
    seg = apont->next;
    ant = NULL;
    while (apont->next != NULL) {
      apont->next = ant;
      apont->pre = seg;
      ant = apont;
      // trocou
      apont = apont->pre;
      seg = apont->next;
    }
    apont->next = ant;
    apont->pre = NULL;
    A.fim = A.inicio;
    A.inicio = apont;
  }
  return A;
}

/*
    @param uma varaivel do tipo Lista, uma variavel do tipo Lista
    @return uma variavel do tipo Lista
    @function obtem os elementos que estao apenas na primeiro parametro
*/

Lista obterComplementar(Lista A, Lista B) {

  Celula *apontA, *apontB;
  int elemento;
  bool veri = false;
  Lista comple = criarLista();

  if (A.tam != 0 && B.tam != 0) {
    apontA = A.inicio;
    do {
      apontB = B.inicio;
      do {
        if (apontB->valor == apontA->valor) {
          veri = true;
        }
        apontB = apontB->next;
      } while (apontB != NULL && veri == false);

      if (veri == false) {
        comple = inserirFim(comple, apontA->valor);
      }

      apontA = apontA->next;
    } while (apontA != NULL);
  }

  return comple;
}

/*
    @param uma variavel do tipo Lista, uma varaivel int
    @return uma variavel do tipo Lista
    @function remove todas as duplicatas de um elemento
*/

Lista removerDuplicata(Lista A, int elemento) {

  Celula *apont, *ant, *prox;
  int ocorrencia;
  if (A.tam > 1) {
    apont = A.inicio;

    while (apont->next != NULL && apont->valor != elemento) {
      apont = apont->next;
    }

    if (apont->valor == elemento) {
      apont = apont->next;

      do {
        if (apont->valor == elemento) {
          if (apont != A.fim) {
            ant = apont->pre;
            prox = apont->next;
            ant->next = prox;
            prox->pre = ant;
            free(apont);
          } else if (apont == A.fim) {
            ant = apont->pre;
            ant->next = NULL;
            A.fim = ant;
            free(apont);
          }
          A.tam--;
        }
        apont = apont->next;
      } while (apont != NULL);
    }
  }
  return A;
}

#endif

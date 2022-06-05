#ifndef _ListaLigada_h
#define _ListaLigada_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Celula {
  char *nome;
  struct Celula *pre;
  struct Celula *next;
} Celula;

typedef struct {
  int tam;
  Celula *inicio;
  Celula *fim;
  Celula *meio;
  int sinalMeio;
  char letra;
} Lista;

Lista criarLista(char);
Lista esvaziarLista(Lista);
char *qualMaior(char *, char *);
void *atualizarMeio(Lista *);
Lista inserirInicio(Lista, char *);
Lista inserirFim(Lista, char *);
void mostrarLista(Lista);
Celula *buscarPosInsMenor(Lista, char *);
Celula *buscarPosInsMaior(Lista, char *);
bool inserirLista(Lista *A, char *nome);
Celula *buscarPos(Lista, char *);
Lista removerUltimo(Lista);
Lista removerInicio(Lista);
bool removerLista(Lista *, char *);

Lista criarLista(char letra) {
  Lista A;
  A.fim = NULL;
  A.inicio = NULL;
  A.meio = NULL;
  A.sinalMeio = 0;
  A.tam = 0;
  A.letra = letra;

  return A;
}

Lista esvaziarLista(Lista A) {

  Celula *apont, *prox;
  if (A.tam != 0) {

    apont = A.inicio;
    do {
      prox = apont->next;
      free(apont);
      apont = prox;
    } while (apont != NULL);

    A.tam = 0;
  }

  return A;
}

char *qualMaior(char *nome1, char *nome2) {
  char *maior = NULL;
  bool veri = false;
  int i = 0, fim;
  int nome1Tam, nome2Tam;

  if (strcmp(nome1, nome2) != 0) {
    // Matias Maties
    // Mat Matias
    // Maaaa Mat
    nome1Tam = strlen(nome1);
    nome2Tam = strlen(nome2);
    fim = strlen(nome1);
    if (nome1Tam > nome2Tam) {
      fim = nome2Tam;
    }
    while (i < fim && veri == false) {
      if (nome1[i] > nome2[i]) {
        veri = true;
        maior = nome1;
      } else if (nome2[i] > nome1[i]) {
        veri = true;
        maior = nome2;
      }
      i++;
    }

    if (veri == false) {
      if (nome1Tam < nome2Tam) {
        maior = nome2;
      } else {
        maior = nome1;
      }
    }
  }
  return maior;
}

void *atualizarMeio(Lista *A) {

  if (A->tam % 2 != 0 && A->sinalMeio < 0) {
    A->meio = A->meio->pre;
    A->sinalMeio = 0;
  } else if (A->tam % 2 != 0 && A->sinalMeio > 0) {
    A->meio = A->meio->next;
    A->sinalMeio = 0;
  }
}

Lista inserirInicio(Lista A, char *nome) {

  Celula *novo = (Celula *)malloc(sizeof(Celula));
  Celula *prim = A.inicio;
  novo->nome = nome;
  novo->pre = NULL;
  A.inicio = novo;

  if (A.tam == 0) {
    novo->next = NULL;
    A.fim = novo;
    A.meio = novo;
    A.sinalMeio = 0;
  } else {
    prim->pre = novo;
    novo->next = prim;
    A.sinalMeio--;
  }
  A.tam++;
  atualizarMeio(&A);

  return A;
}

Lista removerInicio(Lista A) {
  Celula *prim = A.inicio, *prox;
  if (A.tam != 0) {

    A.tam--;
    A.inicio = prim->next;
    if (prim->next == NULL) {
      A.fim = NULL;
      A.meio = NULL;
      A.sinalMeio = 0;
    } else {
      prox = prim->next;
      prox->pre = NULL;
      A.sinalMeio++;
      atualizarMeio(&A);
    }
    free(prim);
  }

  return A;
}

Lista removerUltimo(Lista A) {
  Celula *ultimo = A.fim, *ant;
  if (A.tam != 0) {
    A.tam--;
    A.fim = ultimo->pre;
    // Se tem apenas um elemento
    if (A.inicio->next == NULL) {
      A.inicio = NULL;
      A.meio = NULL;
      A.sinalMeio = 0;
    } else {
      ant = ultimo->pre;
      ant->next = NULL;
      A.sinalMeio--;
      atualizarMeio(&A);
    }
    free(ultimo);
  }

  return A;
}

Lista inserirFim(Lista A, char *nome) {

  Celula *novo = (Celula *)malloc(sizeof(Celula));
  Celula *ultimo = A.fim;
  novo->nome = nome;
  novo->next = NULL;
  A.fim = novo;

  if (A.tam == 0) {
    A.tam++;
    novo->pre = NULL;
    A.inicio = novo;
    A.meio = novo;
    A.sinalMeio = 0;
  } else {
    A.tam++;
    ultimo->next = novo;
    novo->pre = ultimo;
    A.sinalMeio++;
    atualizarMeio(&A);
  }

  return A;
}

void mostrarLista(Lista A) {

  Celula *apont;
  if (A.tam == 0)
    printf("\n Lista Vazia");
  else {
    apont = A.inicio;

    do {
      printf(" %s -", apont->nome);
      apont = apont->next;
    } while (apont != NULL);

    printf("\n   Meio da Lista: %s\n", A.meio->nome);
  }
}

// Procura a primeeira posicao na lista que o nome
// e "maior" que o parametro para a insercao dele na lista
Celula *buscarPosInsMaior(Lista A, char *nome) {
  Celula *aux;
  Celula *posicao = NULL;
  bool achou = false;
  char *maior;

  if (A.inicio->next != NULL) {
    aux = A.meio->next;
    do {

      maior = qualMaior(nome, aux->nome);
      if (qualMaior(nome, aux->nome) == aux->nome) {
        achou = true;
        posicao = aux;
      } else if (maior == NULL) {
        achou = true;
        // Um jeito de indicar que tem duplicata
        posicao = A.meio;
      }

      aux = aux->next;
    } while (aux != NULL && achou == false);

    // se achou for false, insere no fim da lista
    if (achou == false) {
      posicao = NULL;
    }
  }
  return posicao;
}

Celula *buscarPos(Lista A, char *nome) {
  Celula *aux;
  Celula *posicao = NULL;
  bool achou = false;
  char *maior;

  if (A.tam != 0) {

    aux = A.meio;
    if (qualMaior(nome, aux->nome) == nome) {
      aux = A.meio->next;

      do {
        if (strcmp(nome, aux->nome) == 0) {
          achou = true;
          posicao = aux;
        }
        aux = aux->next;
      } while (aux != NULL && achou == false);

    } else if (qualMaior(nome, aux->nome) == aux->nome) {

      aux = A.meio->pre;
      do {
        if (strcmp(nome, aux->nome) == 0) {
          achou = true;
          posicao = aux;
        }
        aux = aux->pre;
      } while (aux != NULL && achou == false);
    } else {
      posicao = A.meio;
      achou = true;
    }
    // se achou for false, insere no inicio da lista
    if (achou == false) {
      posicao = NULL;
    }
  }
  return posicao;
}

// Procura a primeira posicao na lista que o nome
// e "menor" que o parametro para a insercao dele na lista
Celula *buscarPosInsMenor(Lista A, char *nome) {
  Celula *aux;
  Celula *posicao = NULL;
  bool achou = false;
  char *maior;

  if (A.inicio->next != NULL) {
    aux = A.meio->pre;
    do {

      maior = qualMaior(nome, aux->nome);
      if (qualMaior(nome, aux->nome) == nome) {
        achou = true;
        posicao = aux;
      } else if (maior == NULL) {
        achou = true;
        // Um jeito de indicar que tem duplicata
        posicao = A.meio;
      }

      aux = aux->pre;
    } while (aux != NULL && achou == false);

    // se achou for false, insere no inicio da lista
    if (achou == false) {
      posicao = NULL;
    }
  }
  return posicao;
}

bool inserirLista(Lista *A, char *nome) {
  Celula *posicao, *ant, *prox;
  char *nomeNovo, *nomeMeio;
  bool veri = false;

  if (A->tam == 0) {
    *A = inserirInicio(*A, nome);
    veri = true;

  } else {

    if (qualMaior(nome, A->meio->nome) == A->meio->nome) {
      posicao = buscarPosInsMenor(*A, nome);
      if (posicao == NULL) {
        *A = inserirInicio(*A, nome);
        veri = true;
        // senao, insere no meio
      } else if (posicao != A->meio) {
        Celula *novo = (Celula *)malloc(sizeof(Celula));
        novo->nome = nome;

        prox = posicao->next;
        novo->next = prox;
        novo->pre = posicao;
        posicao->next = novo;
        prox->pre = novo;

        A->tam++;
        A->sinalMeio--;
        atualizarMeio(A);
        veri = true;
      }

    } else if (qualMaior(nome, A->meio->nome) == nome) {
      posicao = buscarPosInsMaior(*A, nome);
      if (posicao == NULL) {
        *A = inserirFim(*A, nome);
        veri = true;
        // senao, insere no meio
      } else if (posicao != A->meio) {
        Celula *novo = (Celula *)malloc(sizeof(Celula));
        novo->nome = nome;
        ant = posicao->pre;
        novo->next = posicao;
        novo->pre = ant;
        ant->next = novo;
        posicao->pre = novo;
        A->tam++;
        A->sinalMeio++;

        atualizarMeio(A);
        veri = true;
      }
    }
  }
  return veri;
}

bool removerLista(Lista *A, char *nome) {

  Celula *posicao = buscarPos(*A, nome);
  Celula *ant, *prox;
  bool veri = false;

  if (posicao != NULL) {
    if (posicao == A->inicio) {
      *A = removerInicio(*A);

    } else if (posicao == A->fim) {
      *A = removerUltimo(*A);
    } else {

      if (posicao == A->meio) {
        A->sinalMeio--;
        A->meio = A->meio->pre;
      }
      if (qualMaior(A->meio->nome, nome) == nome) {
        A->sinalMeio--;
      } else if (qualMaior(A->meio->nome, nome) == A->meio->nome) {
        A->sinalMeio++;
      }
      ant = posicao->pre;
      prox = posicao->next;
      ant->next = prox;
      prox->pre = ant;
      A->tam--;
      atualizarMeio(A);
    }
    veri = true;
  }
  return veri;
}
#endif

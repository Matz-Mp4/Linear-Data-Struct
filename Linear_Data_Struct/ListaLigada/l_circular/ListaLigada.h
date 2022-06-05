#ifndef _ListaLigada_h
#define _ListaLigada_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ghost -1

typedef struct Celula {
  int valor;
  struct Celula *next;
} Celula;

typedef Celula *Lista;

Lista criarLista();
int determinarTamanho(Lista);
bool listaVazia(Lista);
void mostrarLista(Lista);
Celula *buscarItem(Lista, int);
int obterItemK(Lista, int);
Lista Insere(Lista, int);
Lista removerItem(Lista, int);
Lista esvaziarLista(Lista A);
void ordenarB(Lista);
Lista inverter(Lista);
Lista removerDuplicata(Lista, int);
Celula *insereProximo(Celula *, int);
bool verificaIgual(Lista, Lista);
bool verificaDuplicata(Lista);
Lista criarListaFrequencia(Lista);
Lista trocar(Lista , Celula *, Celula *);

/*
   @param nenhum
   @retrun uma variavel do tipo Lista

   @function Cria um lista vazia
*/
Lista criarLista() {
  Lista A;
  A = NULL;
  return A;
}

/*
   @param uma variavel do tipo Lista
   @return uma variavel do tipo int

   @function Obtem o tamanho de uma lista
 */

int determinarTamanho(Lista A) {
  int tam = 0;
  Celula *temp;

  if (A != NULL) {
    temp = A;
    tam = 1;
    while (A != temp->next) {
      tam++;
      temp = temp->next;
    }
  }
  return tam;
}

/*
   @param uma variavel do tipo Lista
   @return uma variavel do tipo bool
   @function Verifica se a lista é vazia
 */

bool listaVazia(Lista A) {
  bool vazia = true;
  if (A != NULL)
    vazia = false;
  return vazia;
}

/*
   @param uma variavel do tipo Lista
   @return não há retorno
   @function mostra uma lista
 */

void mostrarLista(Lista p) {
  // a partir do primeiro
  Celula *apont;
  int k;

  if (p == NULL)
    printf("lista vazia \n");
  else {
    printf("\n lista = ");
    apont = p;
    do {
      k = apont->valor;
      printf(" %d ", k);
      apont = apont->next;
    } while (apont != p);
  }

  printf("\n");
}
/*  @param uma variavel do tipo Lista, uma variavel int
    @return um ponteiro do tipo Celula
    @function Localiza a celula na lista pelo seu valor
 */
Celula *buscarItem(Lista A, int item) {
  Celula *pos = NULL;

  if (A != NULL) {
    pos = A;
    while ((pos->valor != item) && (pos->next != A)) {
      pos = pos->next;
    }

    if (pos->valor != item) {
      pos = NULL;
    }
  }
  return pos;
}

/*
    @parm uma variavel do tipo Lista, uma variavel int
    @return uma variavel int
   @function Recupera o k-ésimo item
*/
int obterItemK(Lista A, int k) {
  Celula *apont;
  int i, item;
  item = ghost;

  if (A != NULL) {
    apont = A;
    i = 1;

    if (k > 0) {
      while (apont->next != A && i < k) {
        apont = apont->next;
        i++;
      }
      if (i == k) {
        item = apont->valor;
      }
    }
  }
  return item;
}
/*  @param uma variavel do tipo Lista, uma variavel int
    @return uma variavel do tipo Lista
    @function Insere um novo item no comeco da Lista
*/
Lista Insere(Lista A, int valor) {
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  Celula *ultimaCel;

  if (nova != NULL) {
    nova->valor = valor;
    ultimaCel = A;

    if (ultimaCel != NULL) {

      while (A != ultimaCel->next) {
        ultimaCel = ultimaCel->next;
      }
      nova->next = A;
      ultimaCel->next = nova;

    } else {
      nova->next = nova;
    }
    A = nova;
  }
  return A;
}

/*
    @param uma variavel do tipo Lista, uma variavel int
    @return uma variavel do tipo Lista
    @function Remove um item da lista
*/
Lista removerItem(Lista A, int item) {
  Celula *atual, *antecessor, *fim;
  bool veri = true;
  if (A != NULL) {
    atual = A;
    antecessor = NULL;

    while (atual->valor != item && atual->next != A) {
      antecessor = atual;
      atual = atual->next;
    }
    if (atual->valor == item) {
      if (antecessor != NULL) {
        antecessor->next = atual->next;

      } else if (atual == A && antecessor == NULL) {
        fim = A;

        while (fim->next != A) {
          fim = fim->next;
        }
        fim->next = atual->next;
        A = atual->next;
      } else {
        A = NULL;
      }
      free(atual);
    }
  }
  return A;
}
/*  @param uma variavel do tipo Lista
    @return uma variavel do tipo Lista
    @function Torna a lista vazia
*/
Lista esvaziarLista(Lista A) {
  Celula *aux = NULL, *end;
  if (A != NULL) {
    end = A->next;
    while (aux != A) {
      aux = end;
      end = end->next;
      free(aux);
    }
    A = NULL;
  }
  return A;
}

/*
   @param uma variavel do tipo Lista
   @return uma variavel do tipo Lista
   @function inverte uma Lista
*/
Lista inverter(Lista A) {
  Celula *atual, *prox, *ant;

  if (A != NULL) {
    ant = A;
    atual = ant->next;

    while (atual != A) {
      prox = atual->next;
      atual->next = ant;
      ant = atual;
      atual = prox;
    }
    A = ant;
    atual->next = ant;
  }
  return A;
}
/*
    @param uma variavel do tipo Lista, uma variavel int
    @return uma variavel do tipo Lista
    @function remove todas as duplicatas de um item na Lista
*/
Lista removerDuplicata(Lista A, int item) {
  Celula *apont, *aux, *prox, *ant;
  bool veri = false;
  if (A != NULL) {
    apont = A;

    while (apont->next != A && veri == false) {
      // Sempre vai tirar  se tiver 2 ou mais elementos
      if (apont->valor == item && apont->next != A) {
        veri = true;
        aux = apont->next;
        ant = apont;
        while (aux != A) {

          if (aux->valor == item) {
            ant->next = aux->next;
            free(aux);
          }
          aux = ant->next;
          if (aux->valor != item) {
            ant = ant->next;
          }
        }
      }
      apont = apont->next;
    }
  }
  return A;
}

/*
   @param um ponteiro do tipo Celula, uma variavel int
   @return um ponteiro do tipo Celula
   @funciton Insere o novo elemento na proxima posicao de uma Celula
*/
Celula *insereProximo(Celula *atual, int item) {

  Celula *novo = (Celula *)malloc(sizeof(Celula));

  if (atual != NULL && novo != NULL) {

    novo->valor = item;
    novo->next = atual->next;
    atual->next = novo;
  }
  return novo;
}

/*
   @param uma variavel do tipo Lista
   @return uma variavel do tipo Lista
   @function cria uma uma lista com a quantidade de
   ocorrencia de cada item de uma lista
*/

Lista criarListaFrequencia(Lista A) {

  Lista freq = criarLista();
  Celula *ultimCel, *atual, *aux;
  int repeticao;

  if (A != NULL) {
    atual = A;
    do {
      aux = A;
      repeticao = 0;

      do {
        if (aux->valor == atual->valor) {
          repeticao++;
        }
        aux = aux->next;
      } while (aux != A);

      if (freq == NULL) {
        freq = Insere(freq, repeticao);
        ultimCel = freq;
      } else {
        ultimCel = insereProximo(ultimCel, repeticao);
      }
      atual = atual->next;
    } while (atual != A);
  }
  return freq;
}

/*
   @param Uma variavel do tipo Lista, uma variavel do tipo Lista
   @return uma variavel do tipo bool
   @function Verifica se uma lista é igaul a outra lista independente da ordem
   tendo ou não duplicata
*/
bool verificarIgual(Lista A, Lista B) {
  Lista frequenciaA;
  Celula *ultimaFreq, *atual, *aux;
  int freq, tamA = 0, tamB = 0;
  bool veri = true;

  tamA = determinarTamanho(A);
  tamB = determinarTamanho(B);

  if (tamA == tamB) {
    if (A != NULL && B != NULL) {
      frequenciaA = criarListaFrequencia(A);

      atual = A;
      ultimaFreq = frequenciaA;

      do {
        aux = B;
        freq = 0;
        do {
          if (aux->valor == atual->valor) {
            freq++;
          }
          aux = aux->next;
        } while (aux != B);

        if (freq != ultimaFreq->valor) {
          veri = false;
        }
        atual = atual->next;
        ultimaFreq = ultimaFreq->next;
      } while (veri == true && atual != A);
    }
    frequenciaA = esvaziarLista(frequenciaA);
  }
  return veri;
}

/* @param uma variavel do tipo Lista, um ponteiro para Celula, um ponteiro para Celula 
   @return uma variavel do tipo Lista
   @function as posicoes das celulas entre elas
*/

Lista trocar(Lista A, Celula *cel1, Celula *cel2) {
  
  Celula *antCel1, *antCel2, *aux;
  if (cel1 != NULL && cel2 != NULL) {
    if (cel1 != cel2) {

      // Busca antecessores
      antCel1 = A;
      while (antCel1->next != cel1) {
        antCel1 = antCel1->next;
      }

      antCel2 = A;
      while(antCel2->next != cel2){
        antCel2 = antCel2->next;
      }
      // 1 2 3 4
    if(cel1->next != cel2 && cel2->next != cel1){
      if(cel1->next == cel2){
        cel1->next = cel2->next;
        cel2->next = cel1;
        antCel1->next = cel2;

      //  1 2 3 4  
      }else if( cel2->next == cel1){
        cel2->next = cel1->next;
        cel1->next = cel2;
        antCel2->next = cel1; 
      // 1 2 3 4 5 6 

      }else{
        aux = cel1->next;
        cel1->next = cel2->next;
        cel2->next = aux;
        antCel1->next = cel2;
        antCel2->next = cel1;
      }      
    }
      if(cel1 == A){
        A = cel2;
      }else if(cel2 == A){
        A = cel1;
      }
    }
  }
  return A;
}

#endif

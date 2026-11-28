#include <stdio.h>
#include <stdlib.h>
#include "arvoreBinaria.h"

struct NO {
    struct NO* esq;
    struct NO* dir;
    int matricula; 
};

ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*)malloc(sizeof(ArvBin));
    if (raiz != NULL) {
        *raiz = NULL;
        return raiz;
    }
}

static void liberaNo(struct NO* no) {
    if (no == NULL) return;

    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
}

void libera_ArvBin(ArvBin* raiz) {
    if (raiz == NULL) return;
    
    liberaNo(*raiz); // libera cada nó
    free(raiz); // libera a raiz
}

static int estaVazia_ArvBin(ArvBin* raiz) {
    if (raiz == NULL) return 1;

    if (*raiz == NULL) return 1;

    return 0;
}

void emOrdem(ArvBin* raiz) {
    if (raiz == NULL) return;

    if (*raiz != NULL) {
        emOrdem(&((*raiz)->esq));
        printf("%d ", (*raiz)->matricula);
        emOrdem(&((*raiz)->dir));
    }
}

int insere_ArvBin(ArvBin* raiz, int matricula) {
    if (raiz == NULL) return 0; // se o nó não foi criado

    // Criação do nó que vai ser inserido:
    struct NO* novo = (struct NO*)malloc(sizeof(struct NO));
    if (novo == NULL) return 0; // alocação de memória falhou

    novo->dir = NULL;
    novo->esq = NULL;
    novo->matricula = matricula;

    if (*raiz == NULL) {
        *raiz = novo;
    }
    else {
        // Por não ser uma implementação recursiva, temos que guardar esse no anterior
        struct NO* atual = *raiz;
        struct NO* ant = NULL;

        while (atual != NULL) {
            ant = atual;
            if(matricula == atual->matricula) { // Se inseriu uma matrícula repetida
                free(novo);
                return 0;
            }

            if (matricula > atual->matricula) 
                atual = atual->dir;
            else 
                atual = atual->esq;
        }

        if (matricula > ant->matricula)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

static struct NO* removeAtual(struct NO* atual) {
    struct NO *no1, *no2;

    if (atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    no1 = atual;
    no2 = atual->esq;

    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }

    if (no1 != NULL) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }

    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int matricula) {
    if (raiz == NULL) return 0; // raiz não foi criada
    struct NO* ant = NULL;
    struct NO* atual = *raiz;

    while (atual != NULL) {
        if (matricula == atual->matricula) {
            if (atual == *raiz) {
                *raiz = removeAtual(atual);
            }
            else {
                if (ant->dir == atual) {
                    ant->dir = removeAtual(atual);
                }
                else {
                    ant->esq = removeAtual(atual);
                }
            }
            return 1;
        }
        ant = atual;
        if (matricula > atual->matricula) {
            atual = atual->dir;
        }
        else {
            atual = atual->esq;
        }
    }
    return 0;
}

int consulta_ArvBin(ArvBin* raiz, int matricula) {
    if (raiz == NULL) return 0;

    struct NO* atual = *raiz;
    while (atual != NULL) {
        if (matricula == atual->matricula) return 1; // Matrícula encontrada

        if (matricula > atual->matricula) {
            atual = atual->dir;
        }
        else {
            atual = atual->esq;
        }
    }
    return 0;
}
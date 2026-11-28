#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "filaDin.h"

typedef struct elementoFila {
    Aluno aluno;
    struct elementoFila* proximo;
} ElementoFila;

struct fila {
    ElementoFila* inicio;
    ElementoFila* final;
    int quantidade;
};

Fila* criaFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila == NULL) return 0; // alocação falhou

    fila->inicio = NULL;
    fila->final = NULL;
    fila->quantidade = 0;

    return fila;
}

void liberaFila(Fila* fila) {
    if (fila != NULL) {
        ElementoFila* no;
        while (fila->inicio != NULL) {
            no = fila->inicio;
            fila->inicio = fila->inicio->proximo;
            free(no); 
        }
        free(fila);
    }
}

int filaVazia(Fila *fila) {
    if (fila == NULL) return 0;

    return fila->quantidade == 0;
}

int consultaFila(Fila* fila, Aluno* proximoAluno) {
    if (fila == NULL) return 0;
    if (filaVazia(fila)) {
        printf("Fila de atendimento vazia.\n");
        return 0;
    }

    *proximoAluno = fila->inicio->aluno;
    return 1;
}

int insereFila(Fila* fila, Aluno aluno) {
    if (fila == NULL) return 0;
    
    ElementoFila* no = (ElementoFila*)malloc(sizeof(ElementoFila));
    if (no == NULL) return 0;

    no->aluno = aluno;
    no->proximo = NULL;

    if (filaVazia(fila))
        fila->inicio = no;
    else 
        fila->final->proximo = no;
    fila->final = no;
    fila->quantidade++;
    
    return 1;
}

int removeFila(Fila *fila) {
    if (fila == NULL) return 0;
    if (filaVazia(fila)) {
        printf("Fila de atendimentos vazia...\n");
        return 0;
    }

    ElementoFila* no = fila->inicio;
    fila->inicio = fila->final->proximo;
    free(no);

    if (filaVazia(fila)) {
        fila->final = NULL;
    }

    fila->quantidade--;
    return 1;
}
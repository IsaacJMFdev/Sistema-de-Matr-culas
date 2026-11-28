#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filaPrioridade.h"

typedef struct alunoPrio {
    char nome[30];
    int prioridade;
} AlunoPrio;

struct fila_prioridade {
    AlunoPrio alunos[MAX];
    int quantidade;
};

FilaPrio* cria_FilaPrio() {
    FilaPrio* filaPrio = (FilaPrio*)malloc(sizeof(FilaPrio));
    if (filaPrio != NULL)
        filaPrio->quantidade = 0;

    return filaPrio;
}

void libera_FilaPrio(FilaPrio* filaPrio) {
    if (filaPrio == NULL) return;

    free(filaPrio);
}

int consulta_FilaPrio(FilaPrio* filaPrio, char* nome) {
    if (filaPrio == NULL || filaPrio->quantidade == 0) return 0;

    strcpy(nome, filaPrio->alunos[filaPrio->quantidade - 1].nome);
    return 1;
}

int insere_FilaPrio(FilaPrio* filaPrio, char *nome, int prio) {
    if (filaPrio == NULL || filaPrio->quantidade == MAX) return 0; // Não declarada ou Cheia

    // Esse while calcula a posição em que o aluno vai ficar na fila, o while irá rodar até que i chegue a 0 (prioridade máxima) ou seja menor que
    // alguma prioridade e copiando todos os alunos com menor prioridade para direita, depois o i é salvo para inserir o aluno no indice encontrado
    int i = filaPrio->quantidade - 1;
    while (i >= 0 && filaPrio->alunos[i].prioridade >= prio) {
        filaPrio->alunos[i + 1] = filaPrio->alunos[i];
        i--;
    }

    // strcpy(destino, origem)
    strcpy(filaPrio->alunos[i+1].nome, nome);

    // o aluno desse posição recebe a prioridade passada como argumento
    filaPrio->alunos[i + 1].prioridade = prio;

    // incrementa a quantidade de alunos na fila
    filaPrio->quantidade++;
    return 1;
}

int remove_FilaPrio(FilaPrio* filaPrio) {
    if (filaPrio == NULL || filaPrio->quantidade == 0) return 0; // Não declarada ou vazia

    filaPrio->quantidade--;
    return 1;
}

int estaVazia_FilaPrio(FilaPrio* filaPrio) {
    return filaPrio->quantidade == 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include "aluno.h"

struct hash {
    int qtd, TABLE_SIZE;
    Aluno** itens;
};

Hash* inicializarHash(int TABLE_SIZE) {
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    if (hash != NULL) {
        hash->TABLE_SIZE = TABLE_SIZE;
        hash->itens = (Aluno**)malloc(TABLE_SIZE * sizeof(Aluno*));
    }

    if (hash == NULL) {
        printf("Alocação da Hash falhou, tente novamente...\n");
        return NULL;
    }

    if (hash->itens == NULL) {
        printf("Alocação de item falhou, tente novamente...\n");
        free(hash);
        return NULL;
    }

    hash->qtd = 0;
    for (int i = 0; i < hash->TABLE_SIZE; i++) {
        hash->itens[i] = NULL;
    }

    return hash;
}

void liberarHash(Hash* hash) {
    if(hash != NULL) {
        for (int i = 0; i < hash->TABLE_SIZE; i++) {
            free(hash->itens[i]);
        }
        free(hash->itens);
        free(hash);
    }
}

// Por ser uma função auxiliar de hashTable, recebe esse 'static' só para limitar o uso dele nesse arquivo
static int hashing(int chave, int TABLE_SIZE) {
    return chave % TABLE_SIZE;
}

int insertHash_EnderAberto(Hash *hash, Aluno aluno) {
    if (hash == NULL || hash->qtd == hash->TABLE_SIZE ) {
        return 0;
    }

    int chave = aluno.matricula;
    
    int pos;
    pos = hashing(chave, hash->TABLE_SIZE);
    
    int inicio = pos;

    // Sondagem Linear 
    while (hash->itens[pos] != NULL) {
        // Caso a matrícula já esteja na hash
        if (hash->itens[pos]->matricula == chave) {
            printf("Aluno já matrículado!\n");
            return 0;
        }

        pos = (pos + 1) % hash->TABLE_SIZE; // quando chegar no final da tabela, volta para o inicio

        // Caso já tenha dado a volta completa no array
        if (pos == inicio) {
            printf("Sem espaço para novas matrículas\n");
            return 0;
        }
    }

    // Realiza a cópia do aluno inserido para um novo espaço de memória.
    Aluno* alunoNovo = (Aluno*)malloc(sizeof(Aluno));
    if (alunoNovo == NULL) return 0;

    *alunoNovo = aluno;

    hash->itens[pos] = alunoNovo;
    hash->qtd++;
    return 1;
}

int buscaHash_EnderAberto(Hash *hash, int matricula, Aluno *alunoBuscado) {
    int chave = matricula;
    int pos = hashing(chave, hash->TABLE_SIZE);
    int inicio = pos;

    while (hash->itens[pos] != NULL) {
        // Encontrou
        if (hash->itens[pos]->matricula == matricula) {
            *alunoBuscado = *(hash->itens[pos]);
            return 1;
        }

        // Passa posição
        pos = (pos + 1) % hash->TABLE_SIZE;

        // Voltou ao início
        if (pos == inicio) {
            printf("Aluno não encontrado.\n");
            return 0;
        }
    }
    
    return 0;
}
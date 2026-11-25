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
        pos = (pos + 1) % hash->TABLE_SIZE;

        // Caso a matrícula já esteja na hash
        if (hash->itens[pos]->matricula == chave) {
            printf("Aluno já matrículado!\n");
            return 0;
        }

        // Caso já tenha dado a volta completa no array
        if (pos == inicio) {
            printf("Sem espaço para novas matrículas\n");
            return 0;
        }
    }

    Aluno* alunoNovo = (Aluno*)malloc(sizeof(Aluno));
    if (alunoNovo == NULL) return 0;

    hash->itens[pos] = alunoNovo;
    hash->qtd++;
    return 1;
}
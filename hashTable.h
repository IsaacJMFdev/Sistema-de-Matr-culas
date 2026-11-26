#include "aluno.h"
typedef struct hash Hash;
Hash* inicializarHash(int tamanho);
void liberarHash(Hash* hash);
int insertHash_EnderAberto(Hash* hash, Aluno aluno);
int buscaHash_EnderAberto(Hash* hash, int matricula, Aluno* alunoBuscado);
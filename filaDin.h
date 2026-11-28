#include "aluno.h"
typedef struct fila Fila;
Fila* criaFila();
void liberaFila(Fila* fila);
int consultaFila(Fila* fila, Aluno* proximoAluno);
int insereFila(Fila* fila, Aluno aluno);
int removeFila(Fila* fila);
int filaVazia(Fila* fila);
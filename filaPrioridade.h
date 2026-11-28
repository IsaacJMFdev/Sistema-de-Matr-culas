#define MAX 100
typedef struct fila_prioridade FilaPrio;
FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* filaPrio);
int consulta_FilaPrio(FilaPrio* filaPrio, char* nome); 
int insere_FilaPrio(FilaPrio* filaPrio, char *nome, int prio);
int remove_FilaPrio(FilaPrio* filaPrio);
int estaVazia_FilaPrio(FilaPrio* filaPrio);
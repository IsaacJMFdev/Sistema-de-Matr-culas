typedef struct NO* ArvBin;
ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin* raiz);
int insere_ArvBin(ArvBin* raiz, int matricula);
int remove_ArvBin(ArvBin* raiz, int matricula);
int consulta_ArvBin(ArvBin* raiz, int matricula);
void emOrdem(ArvBin* raiz);
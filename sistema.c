#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "hashTable.h"
#include "arvoreBinaria.h"
#include "filaDin.h"

#define TABLE_SIZE 11

void lerOpcao(int* pointerOpcao) {
    int opcao;
    printf("|Digite a opção: ");
    scanf("%d", &opcao);
    *pointerOpcao = opcao;
}

void menu(int* pointerOpcao) {
    printf("=======+-Sistema de Secretaria-+=======\n");
    printf("|[1] - Cadastrar Aluno                |\n");
    printf("|[2] - Consultar Aluno                |\n");
    printf("|[3] - Listar Matrículas Ativas       |\n");
    printf("|[4] - Trancar Matrícula              |\n");
    printf("|[5] - Chegada para o Atendimento     |\n");
    printf("|[6] - Registrar Urgência             |\n");
    printf("|[7] - Atender Próximo                |\n");
    printf("|[8] - Despachar Requerimento         |\n");
    printf("|[9] - Relatório                      |\n");
    printf("|[0] - Sair                           |\n");
    printf("=======================================\n");
    lerOpcao(pointerOpcao);
}

void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

// 1.
void cadastroAluno(Hash* tabelaAlunos, ArvBin* arvoreMatriculas) {
    Aluno alunoNovo;
    
    printf("Matrícula do aluno: ");
    scanf("%d", &alunoNovo.matricula);
    getchar();
    
    printf("Nome do aluno: ");
    fgets(alunoNovo.nome, sizeof(alunoNovo.nome), stdin);
    alunoNovo.nome[strcspn(alunoNovo.nome, "\n")] = '\0';
    
    printf("Nota 1: ");
    scanf("%f", &alunoNovo.nota1);
    
    printf("Nota 2: ");
    scanf("%f", &alunoNovo.nota2);
    
    printf("Nota 3: ");
    scanf("%f", &alunoNovo.nota3);
    
    limparTela();
    
    if(insertHash_EnderAberto(tabelaAlunos, alunoNovo) && insere_ArvBin(arvoreMatriculas, alunoNovo.matricula)) {
        printf("Aluno cadastrado com sucesso.\n");
    }
    else {
        printf("O cadastro de aluno falhou.\n");
    }
}

// 2.
void consultaAluno(Hash* tabelaAlunos) {
    Aluno alunoBuscado;
    int matriculaBuscada;
    
    printf("Digite a matríucla do aluno que busca: ");
    scanf("%d", &matriculaBuscada);
    
    if(buscaHash_EnderAberto(tabelaAlunos, matriculaBuscada, &alunoBuscado)) {
        limparTela();
        printf("|ALUNO ENCONTRADO:\n");
        printf("|Matrícula: %d\n", alunoBuscado.matricula);
        printf("|Nome: %s\n", alunoBuscado.nome);
        printf("|Nota 1: %.2f\n", alunoBuscado.nota1);
        printf("|Nota 2: %.2f\n", alunoBuscado.nota2);
        printf("|Nota 3: %.2f\n", alunoBuscado.nota3);
        printf("----------------------------------------\n");
    }
    else {
        printf("Aluno não encontrado.\n");
    }
}

// 3.
void listarMatriculasAtivas(ArvBin* arvoreMatriculas) {
    limparTela();
    printf("|Matrículas ativas: ");
    emOrdem(arvoreMatriculas);
    printf("\n------------------------------\n");
}

// 4.
void trancarMatricula(ArvBin* arvoreMatriculas) {
    int matricula;
    printf("Digite a matrícula que deseja trancar: ");
    scanf("%d", &matricula);

    limparTela();

    if (remove_ArvBin(arvoreMatriculas, matricula)) {
        printf("Matrícula [%d] trancada com sucesso.\n", matricula);
        return;
    }
    else {
        printf("Não foi possível realizar o trancamento da matrícula [%d].\n", matricula);
        return;
    }
}

// 5.
void chegadaParaAtendimento(Fila* filaAlunosAtendimento, ArvBin* arvoreMatriculas, Hash* tabelaAlunos) {
    int matricula;
    Aluno* alunoBuscado;

    printf("Digite a matrícula para efetuar o atendimento: ");
    scanf("%d", &matricula);

    limparTela();

    // Procura o aluno na árvore
    if (consulta_ArvBin(arvoreMatriculas, matricula)) {
        // Procura o aluno na hash
        if (buscaHash_EnderAberto(tabelaAlunos, matricula, alunoBuscado)) {
            // Se tudo ocorreu certo, insere na fila
            if(insereFila(filaAlunosAtendimento, *alunoBuscado)) {
                printf("Aluno registrado na fila de atendimento regular.\n");
            }
            else {
                printf("Não foi possível inserir o aluno na fila de atendimento regular.\n");
            }
        }
        else {
            printf("Aluno não cadastrado.\n");
        }
    }
    else {
        printf("Aluno não cadastrado ou com matrícula não ativa.\n");
        return;
    }
}

// 0.
void freeAll(Hash* tabelaAlunos, ArvBin*arvoreMatriculas, Fila* filaAlunosAtendimento) {
    liberarHash(tabelaAlunos);
    libera_ArvBin(arvoreMatriculas);
    liberaFila(filaAlunosAtendimento);
}

int main(){
    Hash* tabelaAlunos = inicializarHash(TABLE_SIZE);
    ArvBin* arvoreMatriculas = cria_ArvBin();
    Fila* filaAlunosAtendimento = criaFila();

    int opcao;
    int* pointerOpcao = &opcao;

    do {
        menu(pointerOpcao);
        switch (opcao) {
            case 1:
                cadastroAluno(tabelaAlunos, arvoreMatriculas);
                break;

            case 2:
                consultaAluno(tabelaAlunos);
                break;

            case 3:
                listarMatriculasAtivas(arvoreMatriculas);
                break;

            case 4:
                trancarMatricula(arvoreMatriculas);
                break;

            case 5:
                chegadaParaAtendimento(filaAlunosAtendimento, arvoreMatriculas, tabelaAlunos);
                break;

            case 0:
                limparTela();
                freeAll(tabelaAlunos, arvoreMatriculas, filaAlunosAtendimento);
                printf("Fechando programa...\n");
                break;
            
            default:
                limparTela();
                printf("Opção Inválida, digite novamente.\n");
                break;
        }

    } while (opcao != 0);
}
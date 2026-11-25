#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "hashTable.h"

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

int main(){
    Hash* tabelaAlunos = inicializarHash(TABLE_SIZE);
    Aluno alunoNovo;
    int opcao;
    int* pointerOpcao = &opcao;

    do {
        menu(pointerOpcao);
        switch (opcao) {
            case 1:
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

                if(insertHash_EnderAberto(tabelaAlunos, alunoNovo)) {
                    printf("Aluno cadastrado com sucesso.\n");
                }
                else {
                    printf("O cadastro de aluno falhou.\n");
                }

                break;

            case 0:
                break;
        }

    } while (opcao != 0);
}
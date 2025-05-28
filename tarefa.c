#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefa.h"



// Contador global para geração de IDs únicos
static int contador_id = 1; // inicia em 1


Tarefa *criar_tarefa() {
    int prioridade;
    char descricao[100];
    char data[11];


    printf("Criando tarefa com ID: %04d\n", contador_id);

    printf("Digite a descricao: ");
    scanf(" %[^\n]", descricao);

    printf("Digite a prioridade (1: alta, 2: media, 3: baixa): ");
    scanf("%d", &prioridade);

    printf("Digite a data (DD-MM-AAAA): ");
    scanf("%s", data);


    Tarefa *nova_tarefa = (Tarefa *)malloc(sizeof(Tarefa));
    if (!nova_tarefa) {
        printf("Erro ao alocar memória para a tarefa.\n");
        exit(1);
    }


    nova_tarefa->id = contador_id++;
    strcpy(nova_tarefa->descricao, descricao);
    nova_tarefa->prioridade = prioridade;
    strcpy(nova_tarefa->data_criacao, data);

    return nova_tarefa;
}


void imprimir_tarefa(Tarefa *tarefa) {
    if (tarefa == NULL) {
        printf("Erro: Tarefa inválida.\n");
        return;
    }
    printf("\n\nID: %04d\n Descrição: %s\n Data de Criação: %s\n Prioridade: %d\n",
           tarefa->id, tarefa->descricao, tarefa->data_criacao, tarefa->prioridade);
}
/*
void imprimir_lista_tarefas(Tarefa *tarefas[], int num_tarefas) {
    printf("Tarefas armazenadas na lista:\n");
    for (int i = 0; i < num_tarefas; i++) {
        imprimir_tarefa(tarefas[i]);
    }
    printf("\n");
}*/

Tarefa* copiar_tarefa(Tarefa *original) {
    Tarefa *copia = (Tarefa *)malloc(sizeof(Tarefa));
    if (copia == NULL) {
        printf("Erro ao alocar memória para a cópia da tarefa.\n");
        exit(1);
    }
    copia->id = original->id;
    strcpy(copia->data_criacao, original->data_criacao);
    return copia;
}


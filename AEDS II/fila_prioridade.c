#include <stdio.h>
#include <stdlib.h>
#include "fila_prioridade.h"



// Fun��o para criar uma nova fila
Fila *criar_fila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (!f) {
        printf("Erro ao alocar mem�ria para a fila.\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// Fun��o para inserir uma tarefa na fila de prioridade
void inserir_na_fila(Fila *f, Tarefa *tarefa) {
    NoFila *novo_no = (NoFila *)malloc(sizeof(NoFila));
    if (!novo_no) {
        printf("Erro ao alocar mem�ria para o n� da fila.\n");
        exit(1);
    }
    novo_no->tarefa = tarefa;
    novo_no->prox = NULL;

    // Inserir na posi��o correta, mantendo a fila ordenada por prioridade
    if (f->inicio == NULL || f->inicio->tarefa->prioridade > tarefa->prioridade) {

        novo_no->prox = f->inicio;
        f->inicio = novo_no;
        if (f->fim == NULL) {
            f->fim = novo_no;
        }
        return;
    }

    // Percorrer a fila para encontrar a posi��o correta
    NoFila *atual = f->inicio;
    while (atual->prox != NULL && atual->prox->tarefa->prioridade <= tarefa->prioridade) {
        atual = atual->prox;
    }

    novo_no->prox = atual->prox;
    atual->prox = novo_no;

    // Atualizar o ponteiro `fim` se o novo n� for inserido no final
    if (novo_no->prox == NULL) {
        f->fim = novo_no;
    }
    printf("Tarefa com ID %04d inserida na fila com prioridade %d.\n", tarefa->id, tarefa->prioridade);
}

// Fun��o para retirar uma tarefa da fila de prioridade
Tarefa *retirar_da_fila(Fila *f) {
    if (verificar_fila_vazia(f)) {
        printf("Erro: A fila est� vazia.\n");
        return NULL;
    }

    NoFila *temp = f->inicio;
    Tarefa *tarefa = temp->tarefa;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(temp);
    return tarefa;
}

// Fun��o para verificar se a fila est� vazia
int verificar_fila_vazia(Fila *f) {
    return (f->inicio == NULL);
}

// Fun��o para liberar a mem�ria da fila
void liberar_fila(Fila *f) {
    NoFila *atual = f->inicio;
    while (atual != NULL) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}

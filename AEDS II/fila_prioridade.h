#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "tarefa.h"


typedef struct no_fila {
    Tarefa *tarefa;
    struct no_fila *prox;
} NoFila;


typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;


Fila *criar_fila();
void inserir_na_fila(Fila *f, Tarefa *tarefa);
Tarefa *retirar_da_fila(Fila *f);
int verificar_fila_vazia(Fila *f);
void liberar_fila(Fila *f);

#endif // FILA_PRIORIDADE_H

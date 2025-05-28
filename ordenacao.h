#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "tarefa.h"



int comparar_data(const char *data1, const char *data2);
void merge(Tarefa *tarefas, int esquerda, int meio, int direita, int (*comparar)(const Tarefa *, const Tarefa *));
void mergeSort(Tarefa *tarefas, int esquerda, int direita, int (*comparar)(const Tarefa *, const Tarefa *));
void ordenar_por_data(Tarefa *tarefas, int n);
void ordenar_por_prioridade(Tarefa *tarefas, int n);
int particao(Tarefa *tarefas, int esquerda, int direita);
void quickSort(Tarefa *tarefas, int esquerda, int direita);
#endif // ORDENACAO_H


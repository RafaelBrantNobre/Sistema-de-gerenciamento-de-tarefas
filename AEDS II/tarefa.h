#ifndef TAREFA_H
#define TAREFA_H

typedef struct{
int id;
char descricao[100];
int prioridade;
char data_criacao[11];
}Tarefa;

Tarefa *criar_tarefa();
void imprimir_tarefa(Tarefa *tarefa);
//void imprimir_lista_tarefas(Tarefa *tarefas[], int num_tarefas);
Tarefa* copiar_tarefa(Tarefa *original);

#endif // TAREFA_H

#include "pesquisa.h"



int *null;

Tarefa *buscar_tarefa_por_id(Tarefa *tarefas[], int size, int id) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (tarefas[mid]->id == id) {
            return tarefas[mid];
        } else if (tarefas[mid]->id < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return null; // Não encontrado
}

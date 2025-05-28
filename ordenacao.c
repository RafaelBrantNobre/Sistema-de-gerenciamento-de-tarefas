#include "ordenacao.h"
#include <string.h>

// Função auxiliar para comparar datas no formato "AAAA-MM-DD"
int comparar_data(const char *data1, const char *data2) {
    return strcmp(data1, data2);  // A comparação funciona para o formato AAAA-MM-DD
}

// Função auxiliar para combinar dois subarrays ordenados em um único ordenado
void merge(Tarefa *tarefas, int esquerda, int meio, int direita, int (*comparar)(const Tarefa *, const Tarefa *)) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    Tarefa L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = tarefas[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = tarefas[meio + 1 + j];

    i = 0; j = 0; k = esquerda;
    while (i < n1 && j < n2) {
        if (comparar(&L[i], &R[j]) <= 0) {
            tarefas[k] = L[i++];
        } else {
            tarefas[k] = R[j++];
        }
        k++;
    }

    while (i < n1) {
        tarefas[k++] = L[i++];
    }
    while (j < n2) {
        tarefas[k++] = R[j++];
    }
}

// Função de ordenação Merge Sort
void mergeSort(Tarefa *tarefas, int esquerda, int direita, int (*comparar)(const Tarefa *, const Tarefa *)) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(tarefas, esquerda, meio, comparar);
        mergeSort(tarefas, meio + 1, direita, comparar);
        merge(tarefas, esquerda, meio, direita, comparar);
    }
}

// Ordena o vetor de tarefas por data de criação usando Merge Sort
void ordenar_por_data(Tarefa *tarefas, int n) {
    mergeSort(tarefas, 0, n - 1, (int (*)(const Tarefa *, const Tarefa *))comparar_data);
}

// Ordena o vetor de tarefas por prioridade usando Merge Sort
void ordenar_por_prioridade(Tarefa *tarefas, int n) {
    mergeSort(tarefas, 0, n - 1, (int (*)(const Tarefa *, const Tarefa *))comparar_data);  // Assumindo que você tem uma função comparar_prioridade similar
}

// Função auxiliar de partição usada pelo Quick Sort
int particao(Tarefa *tarefas, int esquerda, int direita) {
    Tarefa pivot = tarefas[direita];
    int i = (esquerda - 1);

    for (int j = esquerda; j <= direita - 1; j++) {
        if (tarefas[j].id < pivot.id) {
            i++;
            Tarefa temp = tarefas[i];
            tarefas[i] = tarefas[j];
            tarefas[j] = temp;
        }
    }
    Tarefa temp = tarefas[i + 1];
    tarefas[i + 1] = tarefas[direita];
    tarefas[direita] = temp;
    return (i + 1);
}

// Quick Sort para ordenar o vetor de tarefas por id
void quickSort(Tarefa *tarefas, int esquerda, int direita) {
    if (esquerda < direita) {
        int p = particao(tarefas, esquerda, direita);
        quickSort(tarefas, esquerda, p - 1);
        quickSort(tarefas, p + 1, direita);
    }
}

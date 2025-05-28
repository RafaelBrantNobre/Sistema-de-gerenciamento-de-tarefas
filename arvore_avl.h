#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "tarefa.h"

// Estrutura de um nó da árvore AVL
typedef struct NoAVL {
    Tarefa *tarefa;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
} NoAVL;

// Função para criar um novo nó da árvore AVL
NoAVL *criar_no(Tarefa *tarefa);

// Funções de inserção específicas para cada critério de ordenação
NoAVL *inserir_na_arvore_por_id(NoAVL *raiz, Tarefa *tarefa);


// Funções para obter a altura e o fator de balanceamento de um nó
int altura(NoAVL *n);
int fator_balanceamento(NoAVL *n);

// Funções de rotação para balanceamento da árvore AVL
NoAVL *rotacao_direita(NoAVL *y);
NoAVL *rotacao_esquerda(NoAVL *x);

// Função para exibir a árvore em ordem (in-order traversal)

/*void in_order(NoAVL *raiz);*/

// Função para liberar a memória da árvore AVL
void liberar_arvore(NoAVL *raiz);

void inserir_tarefas_balanceadas(NoAVL **raiz, Tarefa *tarefas[], int start, int end);

Tarefa *buscar_tarefa(NoAVL *raiz, int id);

NoAVL *encontrar_menor_no(NoAVL *no);

// Função para remover um nó da árvore AVL
NoAVL *remover_da_arvore(NoAVL *raiz, int id_excluir);

int conta_nos(NoAVL *raiz);

void arvore_para_array(NoAVL *raiz, Tarefa *array, int *index);




#endif // ARVORE_AVL_H

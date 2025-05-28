#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "tarefa.h"

// Estrutura de um n� da �rvore AVL
typedef struct NoAVL {
    Tarefa *tarefa;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
} NoAVL;

// Fun��o para criar um novo n� da �rvore AVL
NoAVL *criar_no(Tarefa *tarefa);

// Fun��es de inser��o espec�ficas para cada crit�rio de ordena��o
NoAVL *inserir_na_arvore_por_id(NoAVL *raiz, Tarefa *tarefa);


// Fun��es para obter a altura e o fator de balanceamento de um n�
int altura(NoAVL *n);
int fator_balanceamento(NoAVL *n);

// Fun��es de rota��o para balanceamento da �rvore AVL
NoAVL *rotacao_direita(NoAVL *y);
NoAVL *rotacao_esquerda(NoAVL *x);

// Fun��o para exibir a �rvore em ordem (in-order traversal)

/*void in_order(NoAVL *raiz);*/

// Fun��o para liberar a mem�ria da �rvore AVL
void liberar_arvore(NoAVL *raiz);

void inserir_tarefas_balanceadas(NoAVL **raiz, Tarefa *tarefas[], int start, int end);

Tarefa *buscar_tarefa(NoAVL *raiz, int id);

NoAVL *encontrar_menor_no(NoAVL *no);

// Fun��o para remover um n� da �rvore AVL
NoAVL *remover_da_arvore(NoAVL *raiz, int id_excluir);

int conta_nos(NoAVL *raiz);

void arvore_para_array(NoAVL *raiz, Tarefa *array, int *index);




#endif // ARVORE_AVL_H

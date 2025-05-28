#include "arvore_avl.h"
#include <stdlib.h>
#include <stdio.h>
#include "tarefa.h"

// Função para criar um novo nó
NoAVL *criar_no(Tarefa *tarefa) {
    NoAVL *novo_no = (NoAVL *)malloc(sizeof(NoAVL));
    if (novo_no != NULL) {
        novo_no->tarefa = tarefa;
        novo_no->esquerda = novo_no->direita = NULL;
        novo_no->altura = 1; // Altura inicial de um novo nó
    }
    return novo_no;
}

// Função para obter a altura de um nó
int altura(NoAVL *n) {
    return (n == NULL) ? 0 : n->altura;
}

// Função para calcular o fator de balanceamento de um nó
int fator_balanceamento(NoAVL *n) {
    return (n == NULL) ? 0 : altura(n->esquerda) - altura(n->direita);
}

// Rotações para balanceamento da árvore AVL
NoAVL *rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    return x;
}

NoAVL *rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));

    return y;
}

// Função de inserção por ID
NoAVL *inserir_na_arvore_por_id(NoAVL *raiz, Tarefa *tarefa) {
    if (raiz == NULL) {
        return criar_no(tarefa);
    }

    if (tarefa->id < raiz->tarefa->id) {
        raiz->esquerda = inserir_na_arvore_por_id(raiz->esquerda, tarefa);
    } else if (tarefa->id > raiz->tarefa->id) {
        raiz->direita = inserir_na_arvore_por_id(raiz->direita, tarefa);
    } else {
        printf("Erro: ID duplicado não permitido.\n");
        return raiz;
    }

    // Atualizar altura e balancear
    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));
    int balance = fator_balanceamento(raiz);

    // Rotações de balanceamento
    if (balance > 1 && tarefa->id < raiz->esquerda->tarefa->id)
        return rotacao_direita(raiz);
    if (balance < -1 && tarefa->id > raiz->direita->tarefa->id)
        return rotacao_esquerda(raiz);
    if (balance > 1 && tarefa->id > raiz->esquerda->tarefa->id) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
    if (balance < -1 && tarefa->id < raiz->direita->tarefa->id) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}



/*
void in_order(NoAVL *raiz) {
    if (raiz != NULL) {
        in_order(raiz->esquerda);  // Percorre o nó esquerdo
        imprimir_tarefa(raiz->tarefa);  // Imprime a tarefa no nó atual
        in_order(raiz->direita);  // Percorre o nó direito
    }
}*/


// Função para liberar a memória de todos os nós da árvore AVL
void liberar_arvore(NoAVL *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);  // Libera o sub-nó esquerdo
        liberar_arvore(raiz->direita);   // Libera o sub-nó direito
        free(raiz->tarefa);              // Libera a tarefa associada ao nó
        free(raiz);                      // Libera o próprio nó
    }
}

void inserir_tarefas_balanceadas(NoAVL **raiz, Tarefa *tarefas[], int start, int end) {
    if (start > end) {
        return;
    }

    // Encontra o elemento do meio para manter o balanceamento da árvore
    int mid = (start + end) / 2;
    *raiz = inserir_na_arvore_por_id(*raiz, tarefas[mid]);  // Usamos a função de inserção por ID como exemplo

    // Chamada recursiva para o lado esquerdo e direito da árvore
    inserir_tarefas_balanceadas(raiz, tarefas, start, mid - 1);
    inserir_tarefas_balanceadas(raiz, tarefas, mid + 1, end);
}

Tarefa *buscar_tarefa(NoAVL *raiz, int id) {
    if (raiz == NULL) {
        return NULL;  // A tarefa não foi encontrada
    }

    if (id == raiz->tarefa->id) {
        return raiz->tarefa;  // Tarefa encontrada
    } else if (id < raiz->tarefa->id) {
        return buscar_tarefa(raiz->esquerda, id);  // Buscar na subárvore esquerda
    } else {
        return buscar_tarefa(raiz->direita, id);  // Buscar na subárvore direita
    }
}


// Função auxiliar para encontrar o nó com o menor valor em uma árvore
NoAVL *encontrar_menor_no(NoAVL *no) {
    while (no->esquerda != NULL) {
        no = no->esquerda;
    }
    return no;
}

// Função para remover um nó da árvore AVL
NoAVL *remover_da_arvore(NoAVL *raiz, int id_excluir) {
    if (raiz == NULL) {
        return raiz; // Nó não encontrado
    }

    // Busca o nó a ser removido
    if (id_excluir < raiz->tarefa->id) {
        raiz->esquerda = remover_da_arvore(raiz->esquerda, id_excluir);
    } else if (id_excluir > raiz->tarefa->id) {
        raiz->direita = remover_da_arvore(raiz->direita, id_excluir);
    } else {
        // Encontrou o nó a ser removido
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            NoAVL *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            // Caso de nó folha
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                // Caso de nó com um único filho
                *raiz = *temp;
            }
            free(temp->tarefa);
            free(temp);
        } else {
            // Caso de nó com dois filhos
            NoAVL *temp = encontrar_menor_no(raiz->direita);

            // Substitui o nó pelo menor valor na subárvore direita
            raiz->tarefa = temp->tarefa;

            // Remove o nó duplicado na subárvore direita
            raiz->direita = remover_da_arvore(raiz->direita, temp->tarefa->id);
        }
    }

    // Caso a árvore tenha apenas um nó
    if (raiz == NULL) {
        return raiz;
    }

    // Atualiza a altura do nó atual
    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));

    // Verifica e corrige o balanceamento
    int balance = fator_balanceamento(raiz);

    // Caso LL
    if (balance > 1 && fator_balanceamento(raiz->esquerda) >= 0) {
        return rotacao_direita(raiz);
    }

    // Caso LR
    if (balance > 1 && fator_balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    // Caso RR
    if (balance < -1 && fator_balanceamento(raiz->direita) <= 0) {
        return rotacao_esquerda(raiz);
    }

    // Caso RL
    if (balance < -1 && fator_balanceamento(raiz->direita) > 0) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }




    return raiz;
}

int conta_nos(NoAVL *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + conta_nos(raiz->esquerda) + conta_nos(raiz->direita);
}

// Função para converter uma árvore AVL em um array
void arvore_para_array(NoAVL *raiz, Tarefa *array, int *index) {
    if (raiz != NULL) {
        arvore_para_array(raiz->esquerda, array, index);
        array[*index] = *(raiz->tarefa);
        (*index)++;
        arvore_para_array(raiz->direita, array, index);
    }
}



#include <stdio.h>
#include <stdlib.h>
#include "manipulacao_arquivos.h"
#include "arvore_avl.h"



    void salvar_em_ordem(NoAVL *raiz) {
        if (raiz != NULL) {
            salvar_em_ordem(raiz->esquerda);
            fprintf(arquivo, "%d|%s|%s|%d\n", raiz->tarefa->id, raiz->tarefa->descricao, raiz->tarefa->data_criacao, raiz->tarefa->prioridade);
            salvar_em_ordem(raiz->direita);
        }


    salvar_em_ordem(arvore_ids);  // Percorre e salva todas as tarefas
    fclose(arquivo);
    printf("Tarefas salvas no arquivo '%s' com sucesso.\n", nome_arquivo);
}

void carregar_tarefas(NoAVL **arvore_ids, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar as tarefas.\n");
        return;
    }

    Tarefa tarefa_temp;
    while (fscanf(arquivo, "%d|%255[^|]|%10[^|]|%d\n", &tarefa_temp.id, tarefa_temp.descricao, tarefa_temp.data_criacao, &tarefa_temp.prioridade) == 4) {
        Tarefa *nova_tarefa = malloc(sizeof(Tarefa));
        if (nova_tarefa == NULL) {
            printf("Erro ao alocar memória para a tarefa carregada.\n");
            fclose(arquivo);
            return;
        }
        *nova_tarefa = tarefa_temp;
        *arvore_ids = inserir_na_arvore_por_id(*arvore_ids, nova_tarefa);
    }
    fclose(arquivo);
    printf("Tarefas carregadas do arquivo '%s' com sucesso.\n", nome_arquivo);
}

#ifndef MANIPULACAO_ARQUIVOS_H_INCLUDED
#define MANIPULACAO_ARQUIVOS_H_INCLUDED

#include "arvore_avl.h"
#include "tarefa.h"


void carregar_tarefas(NoAVL **arvore_ids, const char *nome_arquivo);
  void salvar_em_ordem(NoAVL *raiz);


#endif // MANIPULACAO_ARQUIVOS_H_INCLUDED

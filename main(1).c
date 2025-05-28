#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"
#include "ordenacao.h"
#include "tarefa.h"
#include <locale.h>




// Estrutura de um nó da pilha
typedef struct NoPilha {
    void *dado;              // Ponteiro genérico para armazenar qualquer tipo de dado
    struct NoPilha *proximo; // Próximo elemento da pilha
} NoPilha;

// Estrutura principal da pilha
typedef struct Pilha {
    NoPilha *topo; // Ponteiro para o topo da pilha
    int tamanho;   // Quantidade de elementos na pilha
} Pilha;

// Função para criar uma nova pilha
Pilha *criar_pilha() {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Função para empilhar um elemento na pilha
void empilhar(Pilha *pilha, Tarefa *tarefa) {
    if (pilha == NULL) {
        printf("Erro: Ponteiro para a pilha é nulo.\n");
        return;
    }
    if (tarefa == NULL) {
        printf("Erro: A tarefa a ser empilhada é nula.\n");
        return;
    }

    // Cria uma cópia da tarefa
    Tarefa *copia_tarefa = (Tarefa *)malloc(sizeof(Tarefa));
    if (copia_tarefa == NULL) {
        printf("Erro ao alocar memória para a tarefa na pilha.\n");
        return; // Retorna sem terminar o programa
    }
    *copia_tarefa = *tarefa; // Copia os dados da tarefa original

    // Cria um novo nó para a pilha
    NoPilha *novo_no = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o nó da pilha.\n");
        free(copia_tarefa); // Libera a memória alocada previamente
        return; // Retorna sem terminar o programa
    }
    novo_no->dado = copia_tarefa;
    novo_no->proximo = pilha->topo;
    pilha->topo = novo_no;
    pilha->tamanho++;

    printf("Tarefa com ID %04d empilhada com sucesso.\n", copia_tarefa->id);
}

Tarefa *desempilhar(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Erro: Pilha vazia ou ponteiro nulo.\n");
        return NULL;
    }

    // Remove o nó do topo da pilha
    NoPilha *no_removido = pilha->topo;
    pilha->topo = no_removido->proximo; // Atualiza o topo da pilha
    pilha->tamanho--;

    Tarefa *tarefa = (Tarefa *)no_removido->dado; // Obtém o dado armazenado
    if (tarefa == NULL) {
        printf("Erro: O dado desempilhado está nulo.\n");
    } else {
        printf("Desempilhando tarefa com ID: %04d\n", tarefa->id);
    }

    free(no_removido); // Libera o nó da pilha
    return tarefa; // Retorna o dado desempilhado
}

// Função para verificar se a pilha está vazia
int pilha_vazia(Pilha *pilha) {Tarefa *desempilhar(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Erro: Pilha vazia ou ponteiro nulo.\n");
        return NULL;
    }

    // Remove o nó do topo da pilha
    NoPilha *no_removido = pilha->topo;
    Tarefa *tarefa = (Tarefa *)no_removido->dado; // Obtém o dado armazenado
    if (tarefa == NULL) {
        printf("Erro: O dado desempilhado está nulo.\n");
    } else {
        printf("Desempilhando tarefa com ID: %d\n", tarefa->id);
    }

    pilha->topo = no_removido->proximo; // Atualiza o topo da pilha
    free(no_removido);                  // Libera o nó da pilha
    pilha->tamanho--;

    return tarefa; // Retorna o dado desempilhado
}

    return (pilha->topo == NULL);
}

// Função para liberar a memória da pilha
void liberar_pilha(Pilha *pilha) {
    while (!pilha_vazia(pilha)) {
        desempilhar(pilha);
    }
    free(pilha);
}

// Função para obter o tamanho da pilha
int tamanho_pilha(Pilha *pilha) {
    return pilha->tamanho;
}


// Função para salvar tarefas em um arquivo
void salvar_tarefas(NoAVL *arvore_ids, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as tarefas.\n");
        return;
    }

    // Função auxiliar para percorrer a árvore em ordem e salvar as tarefas
    void salvar_em_ordem(NoAVL *raiz) {
        if (raiz != NULL) {
            salvar_em_ordem(raiz->esquerda);
            fprintf(arquivo, "%d|%s|%s|%d\n", raiz->tarefa->id, raiz->tarefa->descricao, raiz->tarefa->data_criacao, raiz->tarefa->prioridade);
            salvar_em_ordem(raiz->direita);
        }
    }

    salvar_em_ordem(arvore_ids);  // Percorre e salva todas as tarefas
    fclose(arquivo);
    printf("Tarefas salvas no arquivo '%s' com sucesso.\n", nome_arquivo);
}

// Função para ler e exibir o conteúdo do arquivo
void ler_arquivo_para_verificacao(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    char linha[256];
    printf("Conteúdo do arquivo '%s':\n", nome_arquivo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    fclose(arquivo);
}

void excluir_tarefa_do_arquivo(const char *nome_arquivo, int id_excluir) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(arquivo); // Fecha o arquivo original para evitar vazamentos de recurso
        return;
    }

    int id, prioridade;
    char descricao[256], data_criacao[11];
    while (fscanf(arquivo, "%d|%255[^|]|%10[^|]|%d\n", &id, descricao, data_criacao, &prioridade) == 4) {
        if (id != id_excluir) {
            fprintf(temp, "%d|%s|%s|%d\n", id, descricao, data_criacao, prioridade);
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo temporário
    if (remove(nome_arquivo) != 0) {
        perror("Erro ao remover o arquivo original");
        remove("temp.txt"); // Remove o arquivo temporário para não deixar lixo
        return;
    }

    if (rename("temp.txt", nome_arquivo) != 0) {
        perror("Erro ao renomear o arquivo temporário");
        return;
    }
}




int main() {

setlocale(LC_ALL, "Portuguese_Brazil");

    Tarefa *tarefas = NULL;
    int total_tarefas = 0;
    NoAVL *arvore_ids = NULL;
    Pilha *pilha = criar_pilha();
    int prox_id = 1;

    int opcao;
    do {
        printf("Escolha uma opção:\n");
        printf("1. Inserir nova tarefa\n");
        printf("2. Exibir tarefas ordenadas por ID\n");
        printf("3. Exibir tarefas ordenadas por data de criação\n");
        printf("4. Exibir tarefas ordenadas por prioridade\n");
        printf("5. Salvar tarefas em arquivo\n");
        printf("6. Visualizar dados do arquivo\n");
        printf("7. Excluir tarefa e salvar na pilha\n");
        printf("8. Restaurar tarefa da pilha\n");
        printf("9. Limpar histórico da pilha\n");
        printf("10. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                // Realoca memória para a nova tarefa no vetor e verifica se foi bem-sucedido
                Tarefa *nova_alocacao = realloc(tarefas, (total_tarefas + 1) * sizeof(Tarefa));
                if (nova_alocacao == NULL) {
                    printf("Erro ao alocar memória para a nova tarefa.\n");
                    exit(1);
                }
                tarefas = nova_alocacao;

                // Atribui o próximo ID automaticamente e incrementa o contador
                tarefas[total_tarefas].id = prox_id++;
                printf("ID da tarefa atribuído automaticamente: %04d\n", tarefas[total_tarefas].id);

                // Solicita a descrição da tarefa
                printf("Digite a descrição da tarefa: ");
                getchar();  // Limpa o buffer de entrada
                scanf(" %[^\n]", tarefas[total_tarefas].descricao);  // Lê uma linha completa até o Enter

                // Solicita a data no formato DD/MM/AAAA e converte para AAAA/MM/DD
                int dia, mes, ano;
                printf("Digite a data de criação (DD/MM/AAAA): ");
                if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3) {
                    printf("Erro: Formato de data inválido. Por favor, use o formato DD/MM/AAAA.\n");

                    // Limpa o buffer de entrada para remover qualquer caractere extra
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);

                    prox_id--;  // Reverte o incremento do ID
                    break;
                }

                // Armazena a data no formato AAAA/MM/DD
                snprintf(tarefas[total_tarefas].data_criacao, sizeof(tarefas[total_tarefas].data_criacao), "%04d/%02d/%02d", ano, mes, dia);

                // Exibe e solicita a prioridade
                int prioridade;
                printf("Selecione a prioridade da tarefa:\n");
                printf("1 - Alta\n2 - Média\n3 - Baixa\n");
                printf("Digite a prioridade: ");
                if (scanf("%d", &prioridade) != 1 || prioridade < 1 || prioridade > 3) {
                    printf("Erro: Prioridade inválida. Por favor, selecione entre 1 (Alta), 2 (Média), ou 3 (Baixa).\n");
                    prox_id--;  // Reverte o incremento do ID se a prioridade for inválida
                    break;
                }
                tarefas[total_tarefas].prioridade = prioridade;

                // **Ajuste**: Cria uma cópia da tarefa para inserir na árvore AVL
                Tarefa *nova_tarefa = malloc(sizeof(Tarefa));
                if (nova_tarefa == NULL) {
                    printf("Erro ao alocar memória para a nova tarefa.\n");
                    exit(1);
                }
                *nova_tarefa = tarefas[total_tarefas];  // Copia os dados da tarefa atual

                // Insere a tarefa na árvore AVL com o ID gerado automaticamente
                arvore_ids = inserir_na_arvore_por_id(arvore_ids, nova_tarefa);

                // Incrementa o total de tarefas no vetor
                total_tarefas++;
                break;
            }

case 2:
    // Exibir tarefas ordenadas por ID usando Quick Sort
    printf("Tarefas ordenadas por ID:\n");

    int n = conta_nos(arvore_ids); // Conta o número de nós na árvore
    Tarefa *tarefas = malloc(n * sizeof(Tarefa));
    if (tarefas == NULL) {
        printf("Erro ao alocar memória para as tarefas.\n");
        break;
    }

    int index = 0;
    arvore_para_array(arvore_ids, tarefas, &index); // Extrai tarefas para o array

    quickSort(tarefas, 0, n - 1); // Ordena tarefas por ID usando Quick Sort

    // Imprime as tarefas ordenadas
    for (int i = 0; i < n; i++) {
        imprimir_tarefa(&tarefas[i]);
    }

    free(tarefas); // Libera a memória alocada para as tarefas
    break;

case 3:
    // Ordena e exibe tarefas por data
    printf("Tarefas ordenadas por data de criação:\n");
    n = conta_nos(arvore_ids); // Reutiliza a lógica do caso 2
    tarefas = malloc(n * sizeof(Tarefa));
    if (tarefas == NULL) {
        printf("Erro ao alocar memória para as tarefas.\n");
        break;
    }

    index = 0;
    arvore_para_array(arvore_ids, tarefas, &index);
    ordenar_por_data(tarefas, n); // Usa Merge Sort para ordenar por data

    for (int i = 0; i < n; i++) {
        imprimir_tarefa(&tarefas[i]);
    }

    free(tarefas);
    break;

case 4:
    // Ordena e exibe tarefas por prioridade
    printf("Tarefas ordenadas por prioridade:\n");
    n = conta_nos(arvore_ids); // Reutiliza a lógica do caso 2
    tarefas = malloc(n * sizeof(Tarefa));
    if (tarefas == NULL) {
        printf("Erro ao alocar memória para as tarefas.\n");
        break;
    }

    index = 0;
    arvore_para_array(arvore_ids, tarefas, &index);
    ordenar_por_prioridade(tarefas, n); // Usa Merge Sort para ordenar por prioridade

    for (int i = 0; i < n; i++) {
        imprimir_tarefa(&tarefas[i]);
    }

    free(tarefas);
    break;
            case 5:
                // Salvar tarefas em um arquivo
                salvar_tarefas(arvore_ids, "tarefas.txt");
                break;

            case 6:
                // Visualizar dados do arquivo
                ler_arquivo_para_verificacao("tarefas.txt");
                break;

case 7: {
    int id_excluir;
    printf("Digite o ID da tarefa a ser excluída: ");
    if (scanf("%d", &id_excluir) != 1) {
        printf("Erro: Entrada inválida.\n");
        break;
    }

    Tarefa *tarefa_excluida = buscar_tarefa(arvore_ids, id_excluir);
    if (tarefa_excluida != NULL) {
        Tarefa *tarefa_para_pilha = malloc(sizeof(Tarefa));
        if (tarefa_para_pilha == NULL) {
            printf("Erro ao alocar memória para salvar a tarefa na pilha.\n");
            break;
        }
        *tarefa_para_pilha = *tarefa_excluida; // Copia os dados antes de remover da árvore

        // Remove da árvore
        arvore_ids = remover_da_arvore(arvore_ids, id_excluir);

        // Adiciona a cópia na pilha
        empilhar(pilha, tarefa_para_pilha);
        printf("Tarefa com ID %04d excluída e salva na pilha.\n", id_excluir);
    } else {
        printf("Erro: Tarefa com ID %04d não encontrada.\n", id_excluir);
    }
    break;
}

case 8: {
    if (pilha_vazia(pilha)) {
        printf("Erro: A pilha está vazia. Não há tarefas para restaurar.\n");
        break;
    }

    // Remove a tarefa da pilha
    Tarefa *tarefa_restaurada = (Tarefa *)desempilhar(pilha);
    if (tarefa_restaurada == NULL) {
        printf("Erro: A tarefa restaurada está nula.\n");
        break;
    }

    // Reinserir a tarefa na árvore AVL
    arvore_ids = inserir_na_arvore_por_id(arvore_ids, tarefa_restaurada);
    printf("Tarefa com ID %04d reinserida na árvore AVL.\n", tarefa_restaurada->id);

    // Realocar o vetor de tarefas para adicionar a tarefa restaurada
    Tarefa *nova_alocacao = realloc(tarefas, (total_tarefas + 1) * sizeof(Tarefa));
    if (nova_alocacao == NULL) {
        printf("Erro ao alocar memória para o vetor de tarefas.\n");
        exit(1);
    }
    tarefas = nova_alocacao;

    // Copiar os dados da tarefa restaurada para o vetor
    tarefas[total_tarefas] = *tarefa_restaurada;
    total_tarefas++;

    printf("Tarefa com ID %d também adicionada ao vetor de tarefas.\n", tarefa_restaurada->id);
    break;
}


            case 9: {
                           if (pilha_vazia(pilha)) {
                    printf("Erro: A pilha já está vazia..\n");
                    break;
                }
 liberar_pilha(pilha);
     printf("Tarefas excluidas da pilha.\n");
                break;

            }

            case 10:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 10);

    // Libera a memória
    liberar_pilha(pilha);
    liberar_arvore(arvore_ids);
    free(tarefas);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"
#include "ordenacao.h"
#include "tarefa.h"
#include <locale.h>




// Estrutura de um n� da pilha
typedef struct NoPilha {
    void *dado;              // Ponteiro gen�rico para armazenar qualquer tipo de dado
    struct NoPilha *proximo; // Pr�ximo elemento da pilha
} NoPilha;

// Estrutura principal da pilha
typedef struct Pilha {
    NoPilha *topo; // Ponteiro para o topo da pilha
    int tamanho;   // Quantidade de elementos na pilha
} Pilha;

// Fun��o para criar uma nova pilha
Pilha *criar_pilha() {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("Erro ao alocar mem�ria para a pilha.\n");
        exit(1);
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Fun��o para empilhar um elemento na pilha
void empilhar(Pilha *pilha, Tarefa *tarefa) {
    if (pilha == NULL) {
        printf("Erro: Ponteiro para a pilha � nulo.\n");
        return;
    }
    if (tarefa == NULL) {
        printf("Erro: A tarefa a ser empilhada � nula.\n");
        return;
    }

    // Cria uma c�pia da tarefa
    Tarefa *copia_tarefa = (Tarefa *)malloc(sizeof(Tarefa));
    if (copia_tarefa == NULL) {
        printf("Erro ao alocar mem�ria para a tarefa na pilha.\n");
        return; // Retorna sem terminar o programa
    }
    *copia_tarefa = *tarefa; // Copia os dados da tarefa original

    // Cria um novo n� para a pilha
    NoPilha *novo_no = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        printf("Erro ao alocar mem�ria para o n� da pilha.\n");
        free(copia_tarefa); // Libera a mem�ria alocada previamente
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

    // Remove o n� do topo da pilha
    NoPilha *no_removido = pilha->topo;
    pilha->topo = no_removido->proximo; // Atualiza o topo da pilha
    pilha->tamanho--;

    Tarefa *tarefa = (Tarefa *)no_removido->dado; // Obt�m o dado armazenado
    if (tarefa == NULL) {
        printf("Erro: O dado desempilhado est� nulo.\n");
    } else {
        printf("Desempilhando tarefa com ID: %04d\n", tarefa->id);
    }

    free(no_removido); // Libera o n� da pilha
    return tarefa; // Retorna o dado desempilhado
}

// Fun��o para verificar se a pilha est� vazia
int pilha_vazia(Pilha *pilha) {Tarefa *desempilhar(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        printf("Erro: Pilha vazia ou ponteiro nulo.\n");
        return NULL;
    }

    // Remove o n� do topo da pilha
    NoPilha *no_removido = pilha->topo;
    Tarefa *tarefa = (Tarefa *)no_removido->dado; // Obt�m o dado armazenado
    if (tarefa == NULL) {
        printf("Erro: O dado desempilhado est� nulo.\n");
    } else {
        printf("Desempilhando tarefa com ID: %d\n", tarefa->id);
    }

    pilha->topo = no_removido->proximo; // Atualiza o topo da pilha
    free(no_removido);                  // Libera o n� da pilha
    pilha->tamanho--;

    return tarefa; // Retorna o dado desempilhado
}

    return (pilha->topo == NULL);
}

// Fun��o para liberar a mem�ria da pilha
void liberar_pilha(Pilha *pilha) {
    while (!pilha_vazia(pilha)) {
        desempilhar(pilha);
    }
    free(pilha);
}

// Fun��o para obter o tamanho da pilha
int tamanho_pilha(Pilha *pilha) {
    return pilha->tamanho;
}


// Fun��o para salvar tarefas em um arquivo
void salvar_tarefas(NoAVL *arvore_ids, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as tarefas.\n");
        return;
    }

    // Fun��o auxiliar para percorrer a �rvore em ordem e salvar as tarefas
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

// Fun��o para ler e exibir o conte�do do arquivo
void ler_arquivo_para_verificacao(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    char linha[256];
    printf("Conte�do do arquivo '%s':\n", nome_arquivo);
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
        perror("Erro ao criar o arquivo tempor�rio");
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

    // Substitui o arquivo original pelo tempor�rio
    if (remove(nome_arquivo) != 0) {
        perror("Erro ao remover o arquivo original");
        remove("temp.txt"); // Remove o arquivo tempor�rio para n�o deixar lixo
        return;
    }

    if (rename("temp.txt", nome_arquivo) != 0) {
        perror("Erro ao renomear o arquivo tempor�rio");
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
        printf("Escolha uma op��o:\n");
        printf("1. Inserir nova tarefa\n");
        printf("2. Exibir tarefas ordenadas por ID\n");
        printf("3. Exibir tarefas ordenadas por data de cria��o\n");
        printf("4. Exibir tarefas ordenadas por prioridade\n");
        printf("5. Salvar tarefas em arquivo\n");
        printf("6. Visualizar dados do arquivo\n");
        printf("7. Excluir tarefa e salvar na pilha\n");
        printf("8. Restaurar tarefa da pilha\n");
        printf("9. Limpar hist�rico da pilha\n");
        printf("10. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                // Realoca mem�ria para a nova tarefa no vetor e verifica se foi bem-sucedido
                Tarefa *nova_alocacao = realloc(tarefas, (total_tarefas + 1) * sizeof(Tarefa));
                if (nova_alocacao == NULL) {
                    printf("Erro ao alocar mem�ria para a nova tarefa.\n");
                    exit(1);
                }
                tarefas = nova_alocacao;

                // Atribui o pr�ximo ID automaticamente e incrementa o contador
                tarefas[total_tarefas].id = prox_id++;
                printf("ID da tarefa atribu�do automaticamente: %04d\n", tarefas[total_tarefas].id);

                // Solicita a descri��o da tarefa
                printf("Digite a descri��o da tarefa: ");
                getchar();  // Limpa o buffer de entrada
                scanf(" %[^\n]", tarefas[total_tarefas].descricao);  // L� uma linha completa at� o Enter

                // Solicita a data no formato DD/MM/AAAA e converte para AAAA/MM/DD
                int dia, mes, ano;
                printf("Digite a data de cria��o (DD/MM/AAAA): ");
                if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3) {
                    printf("Erro: Formato de data inv�lido. Por favor, use o formato DD/MM/AAAA.\n");

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
                printf("1 - Alta\n2 - M�dia\n3 - Baixa\n");
                printf("Digite a prioridade: ");
                if (scanf("%d", &prioridade) != 1 || prioridade < 1 || prioridade > 3) {
                    printf("Erro: Prioridade inv�lida. Por favor, selecione entre 1 (Alta), 2 (M�dia), ou 3 (Baixa).\n");
                    prox_id--;  // Reverte o incremento do ID se a prioridade for inv�lida
                    break;
                }
                tarefas[total_tarefas].prioridade = prioridade;

                // **Ajuste**: Cria uma c�pia da tarefa para inserir na �rvore AVL
                Tarefa *nova_tarefa = malloc(sizeof(Tarefa));
                if (nova_tarefa == NULL) {
                    printf("Erro ao alocar mem�ria para a nova tarefa.\n");
                    exit(1);
                }
                *nova_tarefa = tarefas[total_tarefas];  // Copia os dados da tarefa atual

                // Insere a tarefa na �rvore AVL com o ID gerado automaticamente
                arvore_ids = inserir_na_arvore_por_id(arvore_ids, nova_tarefa);

                // Incrementa o total de tarefas no vetor
                total_tarefas++;
                break;
            }

case 2:
    // Exibir tarefas ordenadas por ID usando Quick Sort
    printf("Tarefas ordenadas por ID:\n");

    int n = conta_nos(arvore_ids); // Conta o n�mero de n�s na �rvore
    Tarefa *tarefas = malloc(n * sizeof(Tarefa));
    if (tarefas == NULL) {
        printf("Erro ao alocar mem�ria para as tarefas.\n");
        break;
    }

    int index = 0;
    arvore_para_array(arvore_ids, tarefas, &index); // Extrai tarefas para o array

    quickSort(tarefas, 0, n - 1); // Ordena tarefas por ID usando Quick Sort

    // Imprime as tarefas ordenadas
    for (int i = 0; i < n; i++) {
        imprimir_tarefa(&tarefas[i]);
    }

    free(tarefas); // Libera a mem�ria alocada para as tarefas
    break;

case 3:
    // Ordena e exibe tarefas por data
    printf("Tarefas ordenadas por data de cria��o:\n");
    n = conta_nos(arvore_ids); // Reutiliza a l�gica do caso 2
    tarefas = malloc(n * sizeof(Tarefa));
    if (tarefas == NULL) {
        printf("Erro ao alocar mem�ria para as tarefas.\n");
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
    n = conta_nos(arvore_ids); // Reutiliza a l�gica do caso 2
    tarefas = malloc(n * sizeof(Tarefa));
    if (tarefas == NULL) {
        printf("Erro ao alocar mem�ria para as tarefas.\n");
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
    printf("Digite o ID da tarefa a ser exclu�da: ");
    if (scanf("%d", &id_excluir) != 1) {
        printf("Erro: Entrada inv�lida.\n");
        break;
    }

    Tarefa *tarefa_excluida = buscar_tarefa(arvore_ids, id_excluir);
    if (tarefa_excluida != NULL) {
        Tarefa *tarefa_para_pilha = malloc(sizeof(Tarefa));
        if (tarefa_para_pilha == NULL) {
            printf("Erro ao alocar mem�ria para salvar a tarefa na pilha.\n");
            break;
        }
        *tarefa_para_pilha = *tarefa_excluida; // Copia os dados antes de remover da �rvore

        // Remove da �rvore
        arvore_ids = remover_da_arvore(arvore_ids, id_excluir);

        // Adiciona a c�pia na pilha
        empilhar(pilha, tarefa_para_pilha);
        printf("Tarefa com ID %04d exclu�da e salva na pilha.\n", id_excluir);
    } else {
        printf("Erro: Tarefa com ID %04d n�o encontrada.\n", id_excluir);
    }
    break;
}

case 8: {
    if (pilha_vazia(pilha)) {
        printf("Erro: A pilha est� vazia. N�o h� tarefas para restaurar.\n");
        break;
    }

    // Remove a tarefa da pilha
    Tarefa *tarefa_restaurada = (Tarefa *)desempilhar(pilha);
    if (tarefa_restaurada == NULL) {
        printf("Erro: A tarefa restaurada est� nula.\n");
        break;
    }

    // Reinserir a tarefa na �rvore AVL
    arvore_ids = inserir_na_arvore_por_id(arvore_ids, tarefa_restaurada);
    printf("Tarefa com ID %04d reinserida na �rvore AVL.\n", tarefa_restaurada->id);

    // Realocar o vetor de tarefas para adicionar a tarefa restaurada
    Tarefa *nova_alocacao = realloc(tarefas, (total_tarefas + 1) * sizeof(Tarefa));
    if (nova_alocacao == NULL) {
        printf("Erro ao alocar mem�ria para o vetor de tarefas.\n");
        exit(1);
    }
    tarefas = nova_alocacao;

    // Copiar os dados da tarefa restaurada para o vetor
    tarefas[total_tarefas] = *tarefa_restaurada;
    total_tarefas++;

    printf("Tarefa com ID %d tamb�m adicionada ao vetor de tarefas.\n", tarefa_restaurada->id);
    break;
}


            case 9: {
                           if (pilha_vazia(pilha)) {
                    printf("Erro: A pilha j� est� vazia..\n");
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
                printf("Op��o inv�lida. Tente novamente.\n");
        }

    } while (opcao != 10);

    // Libera a mem�ria
    liberar_pilha(pilha);
    liberar_arvore(arvore_ids);
    free(tarefas);

    return 0;
}

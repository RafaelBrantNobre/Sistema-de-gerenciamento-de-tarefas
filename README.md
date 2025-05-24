# Sistema de Gerenciamento de Tarefas - AEDs II

### Autor
Rafael Ribeiro Brant Nobre

---

## Descrição do Projeto

Este sistema foi desenvolvido como parte da disciplina de Algoritmos e Estruturas de Dados II, com o objetivo de organizar, priorizar e gerenciar tarefas de forma eficiente utilizando estruturas de dados avançadas.

---

## Tecnologias e Conceitos Utilizados

- Linguagem: C
- Estruturas de Dados:
  - Árvore AVL (armazenamento e busca por ID)
  - Fila de Prioridade (organização por nível de prioridade)
  - Pilha (backup/restauração de tarefas excluídas)
- Algoritmos:
  - Ordenação: QuickSort, MergeSort, InsertionSort
  - Busca: Binária e Linear
- Modularização: Projeto dividido em múltiplos arquivos `.c` e `.h` para organização e manutenção

---

## Funcionalidades

- Inserir Tarefas: com ID único, descrição, data e prioridade
- Excluir Tarefas: com envio automático para a pilha de backup
- Restaurar Tarefas: a partir da pilha
- Ordenar Tarefas: por data ou prioridade
- Buscar Tarefas: por ID (busca binária)
- Interface em Linha de Comando: menu interativo baseado em `switch case`

---

## Estrutura do Projeto
├── main.c # Arquivo principal e menu do sistema
├── tarefa.c/.h # Struct e funções relacionadas às tarefas
├── fila.c/.h # Implementação da fila de prioridade
├── pilha.c/.h # Implementação da pilha de backup
├── arvore_avl.c/.h # Estrutura da árvore AVL
├── ordenacao.c/.h # Funções de ordenação e busca


---

## Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/sistema-gerenciamento-tarefas.git
   cd sistema-gerenciamento-tarefas

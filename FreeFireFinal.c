#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50

// Estrutura que representa um item da mochila
typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item item;
    struct No *proximo;
} No;

typedef No *ListaEncadeada;

// Protótipos das funções
void inicializarListaEncadeada(ListaEncadeada *lista);
void inserirListaEncadeada(ListaEncadeada *lista);
void removerListaEncadeada(ListaEncadeada *lista);
void listarListaEncadeada(const ListaEncadeada lista);
void liberarListaEncadeada(ListaEncadeada *lista);

// Função principal (menu)
int main() {
    ListaEncadeada mochila;
    int opcao;

    inicializarListaEncadeada(&mochila);

    do {
        printf("\n Desafio Código da Ilha – Nível Novato\n");
        printf("-------------------------------------------\n");
        printf("1. Adicionar item à mochila\n");
        printf("2. Remover item da mochila\n");
        printf("3. Listar itens cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirListaEncadeada(&mochila);
                break;
            case 2:
                removerListaEncadeada(&mochila);
                break;
            case 3:
                listarListaEncadeada(mochila);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarListaEncadeada(&mochila);
    return 0;
}

// Inicializa a lista encadeada (vazia)
void inicializarListaEncadeada(ListaEncadeada *lista) {
    *lista = NULL;
}

// Adiciona um item no início da lista
void inserirListaEncadeada(ListaEncadeada *lista) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(novoNo->item.nome, MAX_STR_LEN, stdin);
    novoNo->item.nome[strcspn(novoNo->item.nome, "\n")] = '\0';

    printf("Digite o tipo do item: ");
    fgets(novoNo->item.tipo, MAX_STR_LEN, stdin);
    novoNo->item.tipo[strcspn(novoNo->item.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->item.quantidade);
    getchar();

    novoNo->proximo = *lista;
    *lista = novoNo;

    printf("\n Item adicionado com sucesso!\n");
}

// Remove um item da lista pelo nome
void removerListaEncadeada(ListaEncadeada *lista) {
    if (*lista == NULL) {
        printf("\n A mochila está vazia.\n");
        return;
    }

    char nome[MAX_STR_LEN];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nome, MAX_STR_LEN, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->item.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n Item \"%s\" não encontrado na mochila.\n", nome);
        return;
    }

    if (anterior == NULL)
        *lista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("\n Item \"%s\" removido com sucesso!\n", nome);
}

// Lista todos os itens da mochila
void listarListaEncadeada(const ListaEncadeada lista) {
    if (lista == NULL) {
        printf("\n A mochila está vazia.\n");
        return;
    }

    printf("\n Itens da Mochila:\n");
    printf("-------------------------------------------\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-------------------------------------------\n");

    No *temp = lista;
    while (temp != NULL) {
        printf("%-20s %-15s %-10d\n", temp->item.nome, temp->item.tipo, temp->item.quantidade);
        temp = temp->proximo;
    }
    printf("-------------------------------------------\n");
}

// Libera toda a memória da lista
void liberarListaEncadeada(ListaEncadeada *lista) {
    No *atual = *lista;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}
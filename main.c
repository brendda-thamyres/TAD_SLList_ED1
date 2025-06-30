#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

//struct que define o tipo de dado utilizado
typedef struct Cliente {
    char nome[30];
    int cpf;
    float renda_mensal;
} Cliente;

//lista os dados do cliente
void show(void *c) {
    Cliente *cliente = (Cliente*)c;
    printf("\n_____info_____\n");
    printf("Nome: %s \n", cliente->nome);
    printf("cpf: %d\n", cliente->cpf);
    printf("Renda mensal: %.2f", cliente->renda_mensal);
    printf("\n_____...._____\n");
}

//libera os dados do cliente
void freeCliente(void *data) {
    free(data);
}

//função que compara por cpf
//função que compara por cpf
int cmp(void *key, void *data) {
    int k = *(int *)key;
    Cliente *c = (Cliente *)data;
    return (k == c->cpf);
}

//menu
int main() {
    SLList *clientes = NULL;
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Criar lista\n");
        printf("2 - Inserir Cliente\n");
        printf("3 - Listar Clientes\n");
        printf("4 - Consultar Cliente (por CPF)\n");
        printf("5 - Remover Cliente (por CPF)\n");
        printf("6 - Esvaziar Lista\n");
        printf("7 - Destruir Lista\n");
        printf("0 - Sair\n");
        printf("--> Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            //CRIA A LISTA
            case 1: {
                if (clientes != NULL) {
                    printf("A lista ja foi criada!\n");
                } else {
                    clientes = SLLCreate();
                    if (clientes != NULL) {
                        printf("Lista criada com sucesso.\n");
                    } else {
                        printf("Erro ao criar lista.\n");
                    }
                }
                break;
            }

            //INSERE CLIENTES NA LISTA
            case 2: {
                if (clientes == NULL) {
                    printf("A lista nao foi criada ainda.\n");
                    break;
                }

                //define a quantidade a ser inserida
                int quantidade;
                printf("Quantos clientes deseja inserir? ");
                scanf("%d", &quantidade);

                if (quantidade <= 0) {
                    printf("Quantidade invalida.\n");
                    break;
                }


                // adiciona cliente por cliente
                for (int i = 0; i < quantidade; i++) {
                    printf("\n--- Cliente %d ---\n", i + 1);

                    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
                    if (c == NULL) {
                        printf("Erro ao alocar memoria para cliente.\n");
                        continue;
                    }

                    //registra os dados do cliente atual
                    printf("Nome: ");
                    getchar(); 
                    fgets(c->nome, sizeof(c->nome), stdin);
                    c->nome[strcspn(c->nome, "\n")] = '\0';
                    
                    printf("CPF: ");
                    scanf("%d", &c->cpf);

                    printf("Renda mensal: ");
                    scanf("%f", &c->renda_mensal);


                    if (SLLInsert(clientes, c) == 0) {
                        printf("Cliente inserido com sucesso.\n");
                    } else {
                        printf("Erro ao inserir cliente.\n");
                        free(c);
                    }
                }

                break;
            }

            //  LISTA TODOS OS CLIENTES
            case 3: {
                if (clientes == NULL) {
                    printf("A lista nao foi criada.\n");
                } else if (clientes->nElms == 0) {
                    printf("Lista vazia.\n");
                } else {
                    printf("\n=== Lista de Clientes ===\n");
                    SLLList(clientes, show);
                }
                break;
            }

            //CONSULTA OS CLIENTES POR CPF
            case 4: {
                if (clientes == NULL) {
                    printf("A lista nao foi criada ainda.\n");
                    break;
                }

                int cpfBusca;
                printf("Digite o CPF do cliente a consultar: ");
                scanf("%d", &cpfBusca);

                Cliente *c = (Cliente *)SLLQuery(clientes, &cpfBusca, cmp);
                if (c != NULL) {
                    printf("Cliente encontrado:\n");
                    show(c);
                } else {
                    printf("Cliente nao encontrado.\n");
                }
                break;
            }

            // REMOVE O CLIENTE POR CPF
            case 5: {
                if (clientes == NULL) {
                    printf("A lista nao foi criada ainda.\n");
                    break;
                }

                int cpfRemove;
                printf("Digite o CPF do cliente a remover: ");
                scanf("%d", &cpfRemove);

                Cliente *c = (Cliente *)SLLRemove(clientes, &cpfRemove, cmp);
                if (c != NULL) {
                    printf("Cliente removido com sucesso:\n");
                    show(c);
                    freeCliente(c);
                } else {
                    printf("Cliente nao encontrado.\n");
                }
                break;
            }

            /// ESVAZIA A LISTA
            case 6: {
                if (clientes == NULL) {
                    printf("A lista nao foi criada ainda.\n");
                } else {
                    SLLEmpty(clientes, freeCliente);
                    printf("Lista esvaziada com sucesso.\n");
                }
                break;
            }

            /// DESTRÓI A LISTA
            case 7: {
                if (clientes == NULL) {
                    printf("A lista nao foi criada ainda.\n");
                } else if (clientes->nElms != 0) {
                    printf("Nao e possivel destruir. A lista ainda contem elementos.\n");
                } else {
                    SLLDestroy(clientes);
                    clientes = NULL;
                    printf("Lista destruida com sucesso.\n");
                }
                break;
            }

            /// SAI DO PROGRAMA
            case 0: {
                if (clientes != NULL) {
                    SLLEmpty(clientes, freeCliente);
                    SLLDestroy(clientes);
                }
                printf("Programa encerrado.\nObrigada por usar esse TAD...!");
                break;
            }
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
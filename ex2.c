#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
char* adiciona(char *lista);
char* remover(char *lista);
void listar(char *lista); 

int main() {
    int opcao = 0;
    char *lista = (char *) malloc(sizeof(char) * 1);
    lista[0] = '\0';

    while(opcao != 4) {
        menu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);
        printf("\n");

        switch(opcao) {
            case 1:
                lista = adiciona(lista);
                break;
            case 2:
                lista = remover(lista);
                break;
            case 3: 
                listar(lista);
                break;
            case 4:
                exit(0);
            default:
                printf("Opcao invalida");
                break;
        }
    }

    free(lista);
    return 0;
}

void menu() {
    printf("\n- 1) Adicionar nome\n");
    printf("- 2) Remover nome\n");
    printf("- 3) Listar\n");
    printf("- 4) Sair\n");
}

char* adiciona(char *lista) {
    int tamanho = 0;
    char nome[50];

    printf("Digite o nome desejado: ");
    scanf("%s", nome);
    tamanho = strlen(nome);

    lista = (char *) realloc(lista, sizeof(char) * (tamanho + 1));
    strcat(lista, nome);
    strcat(lista, "$");
    printf("Nome adicionado.\n");
    
    return lista;
}

char* remover(char *lista) {
    int i = 0, j = 0, compara, tamanho;
    char excluir[50];
    char *token[30];

    printf("Qual nome deseja remover? ");
    scanf("%s", excluir);

    token[0] = '\0';
    token[0] = strtok(lista, "$");  
    
    while(token[i] != NULL) {
        i++;
        token[i] = strtok(NULL, "$");
    }

    lista = (char *) realloc(lista, sizeof(char));
    lista[0] = '\0';

    for(j = 0; j < i; j++) {
        compara = strcmp(token[j], excluir);
        tamanho = strlen(token[j]);

        if(compara != 0) {
            lista = (char *) realloc(lista, sizeof(char) * (tamanho + 1));
            strcat(lista, token[j]);
            strcat(lista, "$");
        }
    }

    return lista;
}

void listar(char *lista) {
    int i = 0;

    for(i = 0; lista[i] != '\0'; i++) {
        if(lista[i] != '$') {
            printf("%c", lista[i]);
        }
        else {
            printf("\n");
        }
    }
}
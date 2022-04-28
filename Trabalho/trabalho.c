#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer = NULL;
void *sentinela = NULL;

void menu();
void escolha();
void incluir();
void apagar();
void buscar();
void listar();
void liberar();

#define HEAD (sizeof(int) * 2)
#define TAIL (sizeof(int) * 2 + sizeof( void **))
#define TAMVARIAVEIS (sizeof(int) * 2 + sizeof(void **) * 2) // valores armazenados no inicio do pBuffer (int numNodos; int opcoes; void **head; void **tail;)
#define TAMNOME (sizeof(char) * 10)
#define TAMIDADE (sizeof(int)) 
#define TAMTELEFONE (sizeof(double))
#define TAMPESSOA (TAMNOME + TAMIDADE + TAMTELEFONE) // tamanho de cada contato completo
#define TAMNODO (sizeof(void *) + TAMPESSOA + sizeof(void *)) // tamanho de cada nodo - organizado como "nodo anterior + dados + proximo nodo"
#define POSTERIOR (sizeof(void *) + TAMPESSOA)

int main() {
    pBuffer = (void *) malloc(sizeof(void **));
    sentinela = (void *) malloc(TAMVARIAVEIS);
    *(int *)(sentinela) = 0;
    *(void **)(sentinela + HEAD) = NULL;
    *(void **)(sentinela + TAIL) = NULL;
    
    for(;;) {
        menu();
        escolha();
    }

    return 0;
}

void menu() {
    printf("\n- 1) Incluir");
    printf("\n- 2) Apagar");
    printf("\n- 3) Buscar");
    printf("\n- 4) Listar");
    printf("\n- 5) Sair\n");
}

void escolha() {
    printf("\nFuncionalidade desejada: ");
    scanf("%d", (int *)(sentinela + sizeof(int)));

    switch(*(int *)(sentinela + sizeof(int))) {
            case 1:
                incluir();
                break;
            case 2:
                apagar();
                break;
            case 3: 
                buscar();
                break;
            case 4:
                listar();
                break;
            case 5:
                printf("\nPrograma encerrado.\n");
                liberar();
                free(pBuffer);
                exit(0);
            default:
                printf("Opcao invalida");
                break;
        }
}

void incluir() {
    void *tracer;
    void *novoContato = malloc(TAMNODO);
    *(void **)(novoContato) = NULL;
    *(void **)(novoContato + POSTERIOR) = NULL;

    printf("\nNome: ");
    scanf("%s", (char *)(novoContato + sizeof(void *)) );
    printf("Idade: ");
    scanf("%d", (int *)(novoContato + sizeof(void *) + TAMNOME) );
    printf("Telefone: ");
    scanf("%lf", (double *)(novoContato + sizeof(void *) + TAMNOME + TAMIDADE) );
 
    if(*(int *)sentinela == 0) {
        *(void **)(sentinela + HEAD) = novoContato; 
        *(void **)(sentinela + TAIL) = novoContato;
        *(int *)(sentinela) += 1;
        return;
    }

    pBuffer = *(void **)(sentinela + HEAD); // head
    
    do {

        if( strcmp( (char *)(novoContato + sizeof(void *)), (char *)(pBuffer + sizeof(void *)) ) < 0 ) {
            *(void **)(novoContato) = *(void **)(pBuffer);
            *(void **)(novoContato + POSTERIOR) = pBuffer;

            if (*(int *)sentinela > 1 && *(void **)(pBuffer) != NULL) {
                tracer = *(void **)(pBuffer);
                *(void **)(tracer + POSTERIOR) = novoContato;
            }

            *(void **)(pBuffer) = novoContato;

            if (*(void **)(novoContato) == NULL) {
                *(void **)(sentinela + HEAD) = novoContato;
            }

            *(int *)sentinela += 1;
            return;
        }

        if (*(void **)(pBuffer + POSTERIOR) == NULL) {
            break;
        }

        pBuffer = *(void **)(pBuffer + POSTERIOR);

    } while(pBuffer != NULL);

    *(void **)(novoContato) = pBuffer;
    *(void **)(pBuffer + POSTERIOR) = novoContato;
    *(void **)(sentinela + TAIL) = novoContato;

    *(int *)(sentinela) += 1;
}

void apagar() {
	void *contato = malloc(sizeof(char) * 10);
    void *conector = malloc(TAMNODO);

	pBuffer = *(void **)(sentinela + HEAD);

    printf("Qual contato deseja remover? ");
    scanf("%s", (char *)(contato));

	while(pBuffer) {
        
        if(strcmp(contato, (char *)(pBuffer + sizeof(void **)) ) == 0 ) {

            // possibilidades do nodo anterior
            if(*(void **)(pBuffer) == NULL) {
                *(void **)(sentinela + HEAD) = *(void **)(pBuffer + POSTERIOR);
            }
            else {
                conector = *(void **)(pBuffer);
                *(void **)(conector + POSTERIOR) = *(void **)(pBuffer + POSTERIOR);
            }

            // possibilidades do nodo posterior
            if(*(void **)(pBuffer + POSTERIOR) == NULL) {
                *(void **)(sentinela + TAIL) = *(void **)(pBuffer);
            }
            else {
                conector = *(void **)(pBuffer + POSTERIOR);
                *(void **)(conector) = *(void **)(pBuffer);
            }

            *(int *)(sentinela) -= 1;
            free(pBuffer);
            printf("Contato removido.\n");
        }

	    pBuffer = *(void **)(pBuffer + POSTERIOR);
    }
    free(contato);
}

void buscar() {
    void *compara = malloc(sizeof(char) * 10);
    pBuffer = *(void **)(sentinela + HEAD);

    printf("Qual contato deseja encontrar? ");
    scanf("%s", (char *)(compara));

    while(pBuffer) {
        if( strcmp( (char *)(compara), (char *)(pBuffer + sizeof(void **)) ) == 0 ) {

            printf("\n-------------------------");
            printf("\n   Contato encontrado!\n");
            printf("-------------------------\n");
            printf("\n| Nome: %s\n", (char *)(pBuffer + sizeof(void **)) );
            printf("| Idade: %d\n", *(int *)(pBuffer + sizeof(void **) + TAMNOME) );
            printf("| Telefone: %.lf\n", *(double *)(pBuffer + sizeof(void **) + TAMNOME + TAMIDADE) );

        }

        pBuffer = *(void **)(pBuffer + POSTERIOR);
    }

    free(compara);

}

void listar() {
    pBuffer = *(void **)(sentinela + HEAD);

    printf("\n-------------------------");
    printf("\n         AGENDA\n");
    printf("-------------------------\n");

    while(pBuffer) {
        printf("\n| Nome: %s\n", (char *)(pBuffer + sizeof(void *)) );
        printf("| Idade: %d\n", *(int *)(pBuffer + sizeof(void *) + TAMNOME) );
        printf("| Telefone: %.lf\n", *(double *)(pBuffer + sizeof(void*) + TAMNOME + TAMIDADE) );
        
        pBuffer = *(void **)(pBuffer + sizeof(void*) + TAMPESSOA); 
    }
}

void liberar() {
    void *nodoSeguinte;
    pBuffer = *(void **)(sentinela + HEAD);

    while(pBuffer) {
        nodoSeguinte = *(void **)(pBuffer + POSTERIOR);
        free(pBuffer);
        pBuffer = nodoSeguinte;
    }
    
    free(nodoSeguinte);
    free(sentinela);
}

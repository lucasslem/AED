#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No {
    int valor;
    struct No *pEsq, *pDir;
    int altura;
} Nodo;

void Escolha();
int QuantidadeNos();
void PrimeiroCenario(int quantNos);
void SegundoCenario();
Nodo *Insere(Nodo *pRaiz, int x);
Nodo *NovoNo(int x);
Nodo *Remove(Nodo *pRaiz, int x);
int AlturaDoNo(Nodo *No);
int Maior(int a, int b);
int FB(Nodo *No);
Nodo *Balanceamento(Nodo *pRaiz);
Nodo *RSE(Nodo *pRaiz);
Nodo *RSD(Nodo *pRaiz); 
Nodo *RDE(Nodo *pRaiz);
Nodo *RDD(Nodo *pRaiz);
void Imprime(Nodo *pRaiz, int nivel);
int EhArvoreAvl(Nodo *pRaiz);
void LimparArvore(Nodo *pRaiz);


int main() {
    srand(time(0));

    for(;;) {
        Escolha();
    }

    return 0;
}

void Escolha() {
    int opcao;

    printf("\n\n1. Primeiro cenario\n2. Segundo cenario\n3. Sair\n\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            PrimeiroCenario(QuantidadeNos());
            break;
        case 2:
            SegundoCenario();
            break;
        case 3:
            printf("Programa encerrado.");
            exit(0);
        default:
            printf("Opcao invalida.");
    }
}

int QuantidadeNos() {
    int quantNos = 0;

    printf("Quantidade de nos da arvore: ");
    scanf("%d", &quantNos);

    return quantNos;
}

void PrimeiroCenario(int quantNos) {
    Nodo *pRaiz = NULL;

    int x;

    for(int i = 0; i < quantNos; i++) {
        x = rand() % 1000;
        pRaiz = Insere(pRaiz, x); 
    }

    printf("\n\n---------- ARVORE FORMADA ----------");
    Imprime(pRaiz, 1);

    if(EhArvoreAvl(pRaiz) == 1) {
        printf("\nArvore AVL");
    }
    else {
        printf("\nArvore nao AVL");
    }

    LimparArvore(pRaiz);
}

Nodo *Insere(Nodo *pRaiz, int x) {
    if(pRaiz == NULL) {
        return NovoNo(x);
    }
    else {
        if(x < pRaiz->valor) {
            pRaiz->pEsq = Insere(pRaiz->pEsq, x);
        }
        else if(x > pRaiz->valor) {
            pRaiz->pDir = Insere(pRaiz->pDir, x);
        }
        else {
            printf("Elemento ja estava presente");
        }
    }

    pRaiz->altura = Maior(AlturaDoNo(pRaiz->pEsq), AlturaDoNo(pRaiz->pDir)) + 1;
    pRaiz = Balanceamento(pRaiz); 

    return pRaiz;
}

Nodo *NovoNo(int x) {
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo));

    novo->valor = x;
    novo->pEsq = NULL;
    novo->pDir = NULL;
    novo->altura = 0;

    return novo;
}

Nodo *Remove(Nodo *pRaiz, int x) {
    if(pRaiz == NULL) {
        printf("O valor nao foi encontrado");
        return NULL;
    }

    if(pRaiz->valor == x) {
        
        if(pRaiz->pEsq == NULL && pRaiz->pDir == NULL) {
            free(pRaiz);
            return NULL;
        }

        if(pRaiz->pEsq != NULL && pRaiz->pDir != NULL) {
            Nodo *noAux = pRaiz->pEsq;
            while(noAux->pDir != NULL) {
                noAux = noAux->pDir;
            }
            pRaiz->valor = noAux->valor;
            noAux->valor = x;
            pRaiz->pEsq = Remove(pRaiz->pEsq, x);
            return pRaiz;
        }
        else {
            Nodo *noAux;
            if(pRaiz->pEsq != NULL && pRaiz->pDir == NULL) {
                noAux = pRaiz->pEsq;
            }
            if(pRaiz->pDir != NULL && pRaiz->pEsq == NULL) {
                noAux = pRaiz->pDir;
            }
            free(pRaiz);
            return noAux;
        }
    }
    else {
        if(x < pRaiz->valor) {
            pRaiz->pEsq = Remove(pRaiz->pEsq, x);
        }
        else {
            pRaiz->pDir = Remove(pRaiz->pDir, x);
        }
    }

    pRaiz->altura = Maior(AlturaDoNo(pRaiz->pEsq), AlturaDoNo(pRaiz->pDir)) + 1;
    pRaiz = Balanceamento(pRaiz);

    return pRaiz;
}

int AlturaDoNo(Nodo *No) {
    if(No == NULL) {
        return -1;
    }
    else {
        return No->altura;
    }
}

int Maior(int a, int b) {
    if(a > b) {
        return a;
    }
    else {
        return b;
    }
}

int FB(Nodo *No) {
    if(No == NULL) {
        return 0;
    }
    return (AlturaDoNo(No->pEsq) - AlturaDoNo(No->pDir));
}

Nodo *Balanceamento(Nodo *pRaiz) {
    if(FB(pRaiz) < -1 && FB(pRaiz->pDir) <= 0) {
        pRaiz = RSE(pRaiz);
    }
    else if(FB(pRaiz) < -1 && FB(pRaiz->pDir) > 0) {
        pRaiz = RDD(pRaiz);
    }
    else if(FB(pRaiz) > 1 && FB(pRaiz->pEsq) >= 0) {
        pRaiz = RSD(pRaiz);
    }
    else if(FB(pRaiz) > 1 && FB(pRaiz->pEsq) < 0) {
        pRaiz = RDE(pRaiz);
    }
    
    return pRaiz;
}

Nodo *RSE(Nodo *pRaiz) {
   Nodo *a, *b;

   a = pRaiz->pDir;
   b = a->pEsq;
   a->pEsq = pRaiz;
   pRaiz->pDir = b;

   pRaiz->altura = Maior(AlturaDoNo(pRaiz->pEsq), AlturaDoNo(pRaiz->pDir)) + 1;
   a->altura = Maior(AlturaDoNo(a->pEsq), AlturaDoNo(a->pDir)) + 1;

   return a;
}

Nodo *RSD(Nodo *pRaiz) {
    Nodo *a, *b;

    a = pRaiz->pEsq;
    b = a->pDir;
    a->pDir = pRaiz;
    pRaiz->pEsq = b;

    pRaiz->altura = Maior(AlturaDoNo(pRaiz->pEsq), AlturaDoNo(pRaiz->pDir)) + 1;
    a->altura = Maior(AlturaDoNo(a->pEsq), AlturaDoNo(a->pDir)) + 1;

    return a;
}

Nodo *RDE(Nodo *pRaiz) {
    pRaiz->pEsq = RSE(pRaiz->pEsq);
    return RSD(pRaiz);
}

Nodo *RDD(Nodo *pRaiz) {
    pRaiz->pDir = RSD(pRaiz->pDir);
    return RSE(pRaiz);
}

void Imprime(Nodo *pRaiz, int nivel) {
    // Essa maneira de imprimir foi aprendida no video contido no seguinte link: https://www.youtube.com/watch?v=f9bNq6x7Osk
    if(pRaiz) {
        Imprime(pRaiz->pDir, nivel + 1);
        printf("\n\n");

        for(int i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("%d", pRaiz->valor);
        Imprime(pRaiz->pEsq, nivel + 1);
    }
}

int EhArvoreAvl (Nodo *pRaiz) {
    int fb;

    if(pRaiz == NULL) {
        return 1;
    }

    if(!EhArvoreAvl(pRaiz->pEsq)) {
        return 0;
    }

    if(!EhArvoreAvl(pRaiz->pDir)) {
        return 0;
    }

    fb = FB(pRaiz);

    if(fb > 1 || fb < -1) {
        return 0;
    }
    else {
        return 1;
    }
}

void LimparArvore(Nodo *pRaiz) {
    if(pRaiz != NULL) {
        LimparArvore(pRaiz->pEsq);
        LimparArvore(pRaiz->pDir);
        free(pRaiz);
    }
}

void SegundoCenario() {
    Nodo *pRaiz = NULL;

    printf("---------- Casos inserindo ----------");

    // caso 1
    printf("\n\n\n--- Caso 1 ---\n\n\n");
    pRaiz = Insere(pRaiz, 20);
    pRaiz = Insere(pRaiz, 4);
    Imprime(pRaiz, 1);
    printf("\n\n\nAdicionando 15\n\n\n");
    pRaiz = Insere(pRaiz, 15);
    Imprime(pRaiz, 1);
    pRaiz = Remove(pRaiz, 15);
    printf("\n\n\nAdicionando 8\n\n\n");
    pRaiz = Insere(pRaiz, 8);
    Imprime(pRaiz, 1);
    LimparArvore(pRaiz);
    pRaiz = NULL;

    // caso 2
    printf("\n\n\n--- Caso 2 ---\n\n\n");
    pRaiz = Insere(pRaiz, 20);
    pRaiz = Insere(pRaiz, 4);
    pRaiz = Insere(pRaiz, 26);
    pRaiz = Insere(pRaiz, 3);
    pRaiz = Insere(pRaiz, 9);
    Imprime(pRaiz, 1);
    printf("\n\n\nAdicionando 15\n\n\n");
    pRaiz = Insere(pRaiz, 15);
    Imprime(pRaiz, 1);
    pRaiz = Remove(pRaiz, 15);
    printf("\n\n\nAdicionando 8\n\n\n");
    pRaiz = Insere(pRaiz, 8);
    Imprime(pRaiz, 1);
    LimparArvore(pRaiz);
    pRaiz = NULL;

    // caso 3
    printf("\n\n\n--- Caso 3 ---\n\n\n");
    pRaiz = Insere(pRaiz, 20);
    pRaiz = Insere(pRaiz, 4);
    pRaiz = Insere(pRaiz, 26);
    pRaiz = Insere(pRaiz, 3);
    pRaiz = Insere(pRaiz, 9);
    pRaiz = Insere(pRaiz, 21);
    pRaiz = Insere(pRaiz, 30);
    pRaiz = Insere(pRaiz, 2);
    pRaiz = Insere(pRaiz, 7);
    pRaiz = Insere(pRaiz, 11);
    Imprime(pRaiz, 1);
    printf("\n\n\nAdicionando 15\n\n\n");
    pRaiz = Insere(pRaiz, 15);
    Imprime(pRaiz, 1);
    pRaiz = Remove(pRaiz, 15);
    printf("\n\n\nAdicionando 8\n\n\n");
    pRaiz = Insere(pRaiz, 8);
    Imprime(pRaiz, 1);
    LimparArvore(pRaiz);
    pRaiz = NULL;

    printf("\n\n---------- Casos removendo ----------\n");

    // caso 1
    printf("\n\n\n--- Caso 1 ---\n\n\n");
    pRaiz = Insere(pRaiz, 2);
    pRaiz = Insere(pRaiz, 1);
    pRaiz = Insere(pRaiz, 4);
    pRaiz = Insere(pRaiz, 3);
    pRaiz = Insere(pRaiz, 5);
    Imprime(pRaiz, 1);
    printf("\n\n\nRemovendo 1\n\n\n");
    pRaiz = Remove(pRaiz, 1);
    Imprime(pRaiz, 1);
    LimparArvore(pRaiz);
    pRaiz = NULL;

    // caso 2
    printf("\n\n\n--- Caso 2 ---\n\n\n");
    pRaiz = Insere(pRaiz, 6);
    pRaiz = Insere(pRaiz, 2);
    pRaiz = Insere(pRaiz, 9);
    pRaiz = Insere(pRaiz, 1);
    pRaiz = Insere(pRaiz, 4);
    pRaiz = Insere(pRaiz, 8);
    pRaiz = Insere(pRaiz, 11);
    pRaiz = Insere(pRaiz, 3);
    pRaiz = Insere(pRaiz, 5);
    pRaiz = Insere(pRaiz, 7);
    pRaiz = Insere(pRaiz, 10);
    pRaiz = Insere(pRaiz, 12);
    pRaiz = Insere(pRaiz, 13);
    Imprime(pRaiz, 1);
    printf("\n\n\nRemovendo 1\n\n\n");
    pRaiz = Remove(pRaiz, 1);
    Imprime(pRaiz, 1);
    LimparArvore(pRaiz);
    pRaiz = NULL;

    // caso 3
    printf("\n\n\n--- Caso 3 ---\n\n\n");
    pRaiz = Insere(pRaiz, 5);
    pRaiz = Insere(pRaiz, 2);
    pRaiz = Insere(pRaiz, 8);
    pRaiz = Insere(pRaiz, 1);
    pRaiz = Insere(pRaiz, 3);
    pRaiz = Insere(pRaiz, 7);
    pRaiz = Insere(pRaiz, 10);
    pRaiz = Insere(pRaiz, 4);
    pRaiz = Insere(pRaiz, 6);
    pRaiz = Insere(pRaiz, 9);
    pRaiz = Insere(pRaiz, 11);
    pRaiz = Insere(pRaiz, 12);
    Imprime(pRaiz, 1);
    printf("\n\n\nRemovendo 1\n\n\n");
    pRaiz = Remove(pRaiz, 1);
    Imprime(pRaiz, 1);
    LimparArvore(pRaiz);
}

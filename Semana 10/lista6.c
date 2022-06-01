#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

int *CriaVetor(int tam);
int *CopiaVetor(int tam, int *desordenado);
void Escolha(int tam, int *vetorDesordenado, int *vetorOrdenado);
void InsertionSort(int *data, int tam);
void SelectionSort(int *data, int tam);
void QuickSort(int *data, int left, int right);
void MergeSort(int *data, int left, int right);
void Merge(int *data, int left, int meio, int right);
void ListarVetor(int *data, int tam);
void Verificar(int *data, int tam);

int main() {
    srand(time(NULL));

    int tam; 
    int *vetorDesordenado = NULL;
    int *vetorOrdenado = NULL;
    
    printf("\nQual o tamanho do vetor desejado? ");
    scanf("%d", &tam);

    vetorDesordenado = CriaVetor(tam);

    for(;;) {
        Escolha(tam, vetorDesordenado, vetorOrdenado);
    }

    return 0;
}

void Escolha(int tam, int *vetorDesordenado, int *vetorOrdenado) {
    int escolha;
    struct timeval begin, end;

    printf("\n\n---------- MENU ----------\n\n");
    printf("1. Insertion Sort\n2. Selection Sort\n3. Quick Sort\n4. Merge Sort\n5. Sair\n\nEscolha o algoritmo desejado: ");
    scanf("%d", &escolha);

    switch(escolha) {
        case 1:
            vetorOrdenado = CopiaVetor(tam, vetorDesordenado);
            printf("\nVETOR DESORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);

            gettimeofday(&begin, 0);
            InsertionSort(vetorOrdenado, tam);
            gettimeofday(&end, 0);
            
            printf("\n\nVETOR ORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);
            Verificar(vetorOrdenado, tam);
            printf(" pelo Insertion Sort");
            printf("\nTempo de execucao: %.10f", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6);

            free(vetorOrdenado);
            break;

        case 2:
            vetorOrdenado = CopiaVetor(tam, vetorDesordenado);
            printf("\nVETOR DESORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);

            gettimeofday(&begin, 0);
            SelectionSort(vetorOrdenado, tam);
            gettimeofday(&end, 0);
            
            printf("\n\nVETOR ORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);
            Verificar(vetorOrdenado, tam);
            printf(" pelo Selection Sort");
            printf("\nTempo de execucao: %.10f", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6);

            free(vetorOrdenado);
            break;

        case 3:
            vetorOrdenado = CopiaVetor(tam, vetorDesordenado);
            printf("\nVETOR DESORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);

            gettimeofday(&begin, 0);
            QuickSort(vetorOrdenado, 0, tam - 1);
            gettimeofday(&end, 0);
    
            printf("\n\nVETOR ORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);
            Verificar(vetorOrdenado, tam);
            printf(" pelo Quick Sort");
            printf("\nTempo de execucao: %.10f", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6);

            free(vetorOrdenado);
            break;

        case 4:
            vetorOrdenado = CopiaVetor(tam, vetorDesordenado);
            printf("\nVETOR DESORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);

            gettimeofday(&begin, 0);
            MergeSort(vetorOrdenado, 0, tam - 1);
            gettimeofday(&end, 0);
            
            printf("\n\nVETOR ORDENADO:\n\n");
            ListarVetor(vetorOrdenado, tam);
            Verificar(vetorOrdenado, tam);
            printf(" pelo Merge Sort");
            printf("\nTempo de execucao: %.10f", (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) * 1e-6);
            
            free(vetorOrdenado);
            break;

        case 5:
            free(vetorDesordenado);
            free(vetorOrdenado);
            exit(0);
    }
}

int *CriaVetor(int tam) {
    int x;
    int *vetor = (int *) malloc(sizeof(int) * tam);

    for(int i = 0; i < tam; i++) {
        x = rand() % 1000;
        vetor[i] = x;
    }

    return vetor;
}

int *CopiaVetor(int tam, int *desordenado) {
    int *vetorOrdenado = (int *) malloc(sizeof(int) * tam);

    for(int i = 0; i < tam; i++) {
        vetorOrdenado[i] = desordenado[i];
    }

    return vetorOrdenado;
}

void InsertionSort(int *data, int tam) {
    int i, j, temp;

    for(i = 1; i < tam; i++) {
        temp = data[i];

        for(j = i; j > 0 && data[j - 1] > temp; j--) {
            data[j] = data[j - 1];
        }

        data[j] = temp;
    }
}

void SelectionSort(int *data, int tam){
    int i, j, temp, min, min_id;

    for(i = 0; i < tam - 1; i++) {
        min = data[i];

        for(j = i + 1; j < tam; j++) {
            if(data[j] < min) {
                min = data[j];
                min_id = j;
            }
        }

        temp = data[i];
        data[i] = data[min_id];
        data[min_id] = temp;
        min_id = i + 1;
    }
}

void QuickSort(int *data, int left, int right) {
    int i = left, j = right, temp, mid;
    mid = data[(left + right) / 2];

    do {
        while(data[i] < mid) {
            i++;
        }
        while(mid < data[j]) {
            j--;
        }

        if(i <= j) {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
    } while(i <= j);

    if(left < j) {
        QuickSort(data, left, j);
    }
    if(i < right) {
        QuickSort(data, i, right);
    }
}

void MergeSort(int *data, int left, int right) {
    int meio;

    if(left < right) {
        meio = floor((left + right) / 2);
        MergeSort(data, left, meio);
        MergeSort(data, meio + 1, right);
        Merge(data, left, meio, right);
    }
}

void Merge(int *data, int left, int meio, int right) {
    int i, j, k, p1, p2, tam, *temp;
    int fim1 = 0, fim2 = 0;

    tam = right - left + 1;
    p1 = left;
    p2 = meio + 1;
    temp = (int *) malloc(sizeof(int) * tam);

    if(temp != NULL) {

        for(i = 0; i < tam; i++) {

            if(!fim1 && !fim2) {

                if(data[p1] < data[p2]) {
                    temp[i] = data[p1];
                    p1++;
                }
                else {
                    temp[i] = data[p2];
                    p2++;
                }

                if(p1 > meio) {
                    fim1 = 1;
                }
                if(p2 > right) {
                    fim2 = 1;
                }
            }
            else {
                if(!fim1) {
                    temp[i] = data[p1];
                    p1++;
                }
                else {
                    temp[i] = data[p2];
                    p2++;
                }
            }
        }
    }

    for(j = 0, k = left; j < tam; j++, k++) {
        data[k] = temp[j];
    }

    free(temp);
}

void ListarVetor(int *data, int tam) {
    for(int i = 0; i < tam; i++) {
        printf("%d ", data[i]);
    }
}

void Verificar(int *data, int tam) {
    int i, checar = 0;

    for(i = 1; i < tam; i++) {
        if(data[i] < data[i - 1]) {
            checar = 1;
        }
    }

    if(!checar) {
        printf("\n\n\nVetor ordenado corretamente");
    }
    else {
        printf("\n\n\nVetor ordenado incorretamente");
    }
}

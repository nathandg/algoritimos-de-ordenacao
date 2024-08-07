#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }
        
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

void quick_sort(int arr[], int n) {
    if (n <= 1) return; // Caso base: array de tamanho 0 ou 1 já está ordenado

    int i = 0, j = n - 1;
    int x = arr[n / 2]; // Escolha do pivô

    // Particionamento
    while (i <= j) {
        while (arr[i] < x) {
            i++;
        }

        while (arr[j] > x) {
            j--;
        }

        if (i <= j) {
            // Troca de elementos
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    // Recursão para as subpartições
    if (j > 0) {
        quick_sort(arr, j + 1);
    }

    if (i < n) {
        quick_sort(arr + i, n - i);
    }
}
 
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void gerar_array(int arr[], int tamanho, char *caso) {
    if (strcmp(caso, "melhor") == 0) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = i;
        }
    } else if (strcmp(caso, "medio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = rand() % tamanho;
        }
    } else if (strcmp(caso, "pior") == 0) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = tamanho - i;
        }
    }
}

int main() {
    int tamanhos[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    char *casos[] = {"melhor", "medio", "pior"};

    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int num_casos = sizeof(casos) / sizeof(casos[0]);

    printf("| Tamanho da entrada | Melhor caso | Caso médio | Pior caso |\n");
    printf("|---|---|---|---|\n");

    for (int i = 0; i < num_tamanhos; i++) {
        int tamanho = tamanhos[i];
        double tempos[3];

        int *arr = (int *)malloc(tamanho * sizeof(int));

        for (int j = 0; j < num_casos; j++) {
            char *caso = casos[j];

            gerar_array(arr, tamanho, caso);

            clock_t inicio = clock();
            // insertion_sort(arr, tamanho);
            // bubble_sort(arr, tamanho);
            // selection_sort(arr, tamanho);
            // quick_sort(arr, tamanho);
            mergeSort(arr, 0, tamanho - 1);
            clock_t fim = clock();

            tempos[j] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        }

        printf("| %d | %.6f seg. | %.6f seg. | %.6f seg. |\n", tamanho, tempos[0], tempos[1], tempos[2]);
        free(arr);
    }

    return 0;
}

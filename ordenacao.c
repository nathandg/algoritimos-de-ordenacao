#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { int temp = arr[j];
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

void gerar_array(int arr[], int tamanho, char *caso) {
    if (strcmp(caso, "melhor") == 0) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = i;
        }
    } else if (strcmp(caso, "medio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = rand() % tamanho + 1;
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

        for (int j = 0; j < num_casos; j++) {
            char *caso = casos[j];
            int *arr = (int *)malloc(tamanho * sizeof(int));

            gerar_array(arr, tamanho, caso);

            clock_t inicio = clock();
            // insertion_sort(arr, tamanho);
            // bubble_sort(arr, tamanho);
            selection_sort(arr, tamanho);
            clock_t fim = clock();

            tempos[j] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            // printf("Com %d elementos no %s caso, o tempo foi de %.6f seg.\n", tamanho, caso, tempos[j]);
            free(arr);
        }

        printf("| %d | %.6f seg. | %.6f seg. | %.6f seg. |\n", tamanho, tempos[0], tempos[1], tempos[2]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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

void heapsort(int a[], int n) {
   int i = n / 2, pai, filho, t;
   while(1) {
      if (i > 0) {
          i--;
          t = a[i];
      } else {
          n--;
          if (n <= 0) return;
          t = a[n];
          a[n] = a[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < n) {
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          if (a[filho] > t) {
             a[pai] = a[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      a[pai] = t;
   }
}

void shellSort(int *vet, int size) {
    int i, j, value;
 
    int h = 1;
    while(h < size) {
        h = 3*h+1;
    }

    while (h > 0) {
        for(i = h; i < size; i++) {
            value = vet[i];
            j = i;
            while (j > h-1 && value <= vet[j - h]) {
                vet[j] = vet[j - h];
                j = j - h;
            }
            vet[j] = value;
        }
        h = h/3;
    }
}

void countSort(int inputArray[], int N) {
  
    // Finding the maximum element of 
    // array inputArray[]
    int M = 0;
    for (int i = 0; i < N; i++)
        if (inputArray[i] > M)
            M = inputArray[i];
    
    // Initializing countArray[] with 0
    int* countArray = (int*)calloc(M + 1, sizeof(int));
    
    // Mapping each element of inputArray[] 
    // as an index of countArray[] array
    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;
    
    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];
    
    // Creating outputArray[] from countArray[] array
    int* outputArray = (int*)malloc(N * sizeof(int));
    for (int i = N - 1; i >= 0; i--) {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }
    
    // Copying sorted elements back to inputArray[]
    for (int i = 0; i < N; i++)
        inputArray[i] = outputArray[i];
    
    // Freeing dynamically allocated memory
    free(countArray);
    free(outputArray);
}

// Function to check if an array is sorted
bool is_sorted(int *a, int n) {
    while (--n >= 1) {
        if (a[n] < a[n - 1])
            return false;
    }
    return true;
}

// Function to shuffle the elements of an array
void shuffle(int *a, int n) {
    int i, t, r;
    for (i = 0; i < n; i++) {
        t = a[i];
        r = rand() % n;
        a[i] = a[r];
        a[r] = t;
    }
}

// BogoSort function to sort an array
void bogosort(int *a, int n) {
    while (!is_sorted(a, n))
        shuffle(a, n);
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
            // bubble_sort(arr, tamanho);
            // insertion_sort(arr, tamanho);
            // selection_sort(arr, tamanho);
            // quick_sort(arr, tamanho);
            // mergeSort(arr, 0, tamanho - 1);
            // heapsort(arr, tamanho);
            // shellSort(arr, tamanho);
            // countSort(arr, tamanho);
            bogosort(arr, tamanho);
            clock_t fim = clock();

            tempos[j] = ((double)(fim - inicio)) / (CLOCKS_PER_SEC / 1000); 
            // printf("Tamanho: %d, Caso: %s, Tempo: %.6f ms\n", tamanho, caso, tempos[j]);
        }

        printf("| %d | %.6f ms | %.6f ms | %.6f ms |\n", tamanho, tempos[0], tempos[1], tempos[2]);
        free(arr);
    }

    return 0;
}

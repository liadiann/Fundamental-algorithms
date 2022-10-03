#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void array_filling(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void Print_an_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}

void task(int* arr1, int* arr2, int* arr3, int size1, int size2) {
    int size_2 = size2 - 1;
    for (int i = 0; i < size1; i++) {
        if (i >= size2) arr3[i] = arr1[i] + arr2[size_2];
        else {
            arr3[i] = arr1[i] + arr2[i];
        }
    }
}

int main() {
    int* A;
    int* B;
    int* C;
    int N1, N2;
    srand(time(NULL));
    printf("Введите размерности массивов A и B соответственно: ");
    scanf("%d %d", &N1, &N2);
    A = (int*)malloc(N1*sizeof(int));
    B = (int*)malloc(N2*sizeof(int));
    C = (int*)malloc(N1*sizeof(int));
    array_filling(A, N1);
    Print_an_array(A, N1);
    srand(time(NULL));
    array_filling(B, N2);
    Print_an_array(B, N2);
    task(A, B, C, N1, N2);
    Print_an_array(C, N1);
    return 0;
}
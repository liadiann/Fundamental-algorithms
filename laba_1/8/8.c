#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void variant_a(int n, int* arr1, int* arr2, int* count) {
     for (int i = 0; i < n; i++) {
        if ((i % 2) != 0) {
            arr2[*count] = arr1[i];
            *count = *count + 1;
        }
     }
}

void var_b(int n, int* arr1, int* arr2, int* count) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] % 2 == 0) {
            arr2[*count] = arr1[i];
            *count = *count + 1; 
        }
    }
}

void var_c(int n, int* arr1, int* arr2, int* count, int* index) {
    int max = 0, ind = 0;
    for (int i = 0; i < n; i++) {
        if (max < abs(arr1[i]-arr1[*index])) {
            max = abs(arr1[i] - arr1[*index]);
            ind = i;
        }
    }
    *count = 1;
    arr2[0] = arr1[ind];
}

void var_d(int* arr1, int* arr2, int* index, int* count) {
    int sum = 0;
    for (int i = 0; i < *index; i++) {
        sum = sum + arr1[i];
    }
    *count = 1;
    arr2[0] = sum;
}

void var_e(int* arr1, int* arr2, int n, int* index, int* count) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr1[i] < arr1[*index]) {
            sum = sum + arr1[i];
        }
    }
    *count = 1;
    arr2[0] = sum;
}

void Print_an_array(int* m, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d  ", m[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: program input_file\n");
        return 1;
    }
    FILE* fIn = NULL;
    int n = 0;
    fIn = fopen(argv[1], "r");
    if (fIn == NULL) {
        perror("Ошибка: ");
        return 1;
    }
    int s;
    while(fscanf(fIn, "%d", &s) != EOF) n++;
    if (n > 128) {
        printf("Слишком большой массив!\n");
        return 1;
    }
    int* arr1 = (int*)malloc(sizeof(int)*n);
    if (arr1 == NULL) {
        printf("Ошибка!\n");
        return 1;
    }
    rewind(fIn);
    for(int i = 0; i < n; i++) fscanf(fIn, "%d", &arr1[i]);
    int* arr2 = (int*)malloc(sizeof(int)*n);
    if (arr2 == NULL) {
        printf("Ошибка!\n");
        return 1;
    }
    Print_an_array(arr1, n);
    printf("Переписать в новый массив:\na) числа, стоящие на нечетных позициях\nb) четные числа\nc) для текущего элемента: наиболее далёкое (по значению) от него значение из этого же массива\nd) для текущего элемента: сумму элементов, которые ему предшествуют\ne) для текущего элемента: сумму элементов, которые меньше него.\n");
    char k;
    int count = 0;
    scanf("%c", &k);
    switch (k)
    {
    case 'a':
        variant_a(n, arr1, arr2, &count);
        Print_an_array(arr2, count);
        break;
    case 'b':
        var_b(n, arr1, arr2, &count);
        Print_an_array(arr2, count);
        break;
    case 'c':
        printf("Введите индекс текущего элемента: ");
        int index;
        scanf("%d", &index);
        var_c(n, arr1, arr2, &count, &index);
        Print_an_array(arr2, count);
        break;
    case 'd':
        printf("Введите индекс текущего элемента: ");
        scanf("%d", &index);
        var_d(arr1, arr2, &index, &count);
        Print_an_array(arr2, count);
        break;
    case 'e':
        printf("Введите индекс текущего элемента: ");
        scanf("%d", &index);
        var_e(arr1, arr2, n, &index, &count);
        Print_an_array(arr2, count);
        break;
    }
    free(arr1);
    free(arr2);
    fclose(fIn);
    return 0;
}
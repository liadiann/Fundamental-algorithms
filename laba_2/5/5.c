#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void array_filling(int* arr, int size, int a, int c, int* flag) {
    *flag = 0;
    if (size < 0) {
        *flag = 1;
    }else{
    for (int i = 0; i < size; i++) {
        arr[i] = (rand() % c) + a;
    }
    }
}

void print_an_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}

void find_max_and_min(int* m, int size, int* index_max, int* index_min) {
    *index_max = 0;
    *index_min = 0;
    int max = m[0], min = m[0];
    for (int i = 1; i < size; i++) {
        if (max < m[i]) {
            max = m[i];
            *index_max = i;
        }
        if (min > m[i]) {
            min = m[i];
            *index_min = i;
        }
    }
}

void swap_elements(int* max, int* min) {
    int tmp;
    tmp = *max;
    *max = *min;
    *min = tmp; 
}

void unique_elements(int* arr1, int* arr2, int size, int* count) {
    int f;
    *count = 0;
    for (int i = 0; i < size; i++) {
        f = 0;
        for (int j = 0; j < *count; j++) {
            if (arr1[i] == arr2[j]) {
                f = 1;
            }
        }
        if (f == 0) {
            arr2[*count] = arr1[i];
            *count = *count + 1;
        }
    }
}

int main() {
    int* arr1;
    int N, a, b, c, flag, index_max, index_min, count;
    srand(time(NULL));
    printf("Введите размерность одномерного массива: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Введите положительное число!\n");
        return 1;
    }
    arr1 = (int*)malloc(N*sizeof(int));
    if (arr1 == NULL) {
        printf("Память не выделилась!\n");
        return 2;
    }
    printf("Введите границы диапазона.\na = ");
    scanf("%d", &a);
    if (a < 0) {
        printf("Числа только положительные!\n");
        return 3;
    } 
    printf("b = ");
    scanf("%d", &b);
    if (b < 0) {
        printf("Числа только положительные!\n");
        return 4;
    }
    if (a > b) {
        printf("Неправильно введен диапазон! Первое число должно быть меньше второго\n");
        return 5;
    } 
    c = b - a + 1;
    array_filling(arr1, N, a, c, &flag);
    if (flag == 1) {
        printf("Размер массива должен быть положительным числом!\n");
        return 6;
    }
    print_an_array(arr1, N);
    printf("Выберите действие(1 или 2):\n1. Поменять местами максимальный и минимальный элементы массива.\n2. Создать новый массив, который содержит уникальные элементы исходного массива.\n");
    scanf("%d", &flag);
    if ((flag != 1) && (flag != 2)) {
        printf("Нужно ввести цифру 1 или 2\n");
        return 7;
    }
    if (flag == 1) {
        find_max_and_min(arr1, N, &index_max, &index_min);
        swap_elements(&arr1[index_max], &arr1[index_min]);
        print_an_array(arr1, N);
    }
    if (flag == 2) {
        int* arr2 = (int*)malloc(N*sizeof(int));
        if (arr2 == NULL) {
            printf("Память не выделилась!\n");
            free(arr1);
            return 8;
        }
        unique_elements(arr1, arr2, N, &count);
        print_an_array(arr2, count);
        free(arr2);
    }
    free(arr1);
    return 0;
}
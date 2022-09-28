#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void array_filling(int* m, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        m[i] = rand();
    }
}

void Print_an_array(int* m, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d  ", m[i]);
    }
    printf("\n");
}

void Find_max_and_min(int* m, int size, int* max, int* min) {
    int index_max = 0, index_min = 0;
    for (int i = 1; i < size; i++) {
        if (*max < m[i]) {
            *max = m[i];
            index_max = i;
        }
        if (*min > m[i]) {
            *min = m[i];
            index_min = i;
        }
    }
    m[index_max] = *min;
    m[index_min] = *max;
}

int main() {
    int size;
    printf("Введите размерность массива: ");
    scanf("%d", &size);
    int m[size];
    array_filling(m, size);
    int max = m[0], min = m[0];
    Print_an_array(m, size);
    Find_max_and_min(m, size, &max, &min);
    printf("Максимальный элемент массива: %d\n", max);
    printf("Минимальный элемент массива: %d\n", min);
    Print_an_array(m, size);
    return 0;
}
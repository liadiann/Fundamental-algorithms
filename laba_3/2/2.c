#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define invalid_input -1
#define overflow -2 
#define memory_allocation_error -3
#define error -4
#define success 0

double C(int n, int k)
{
    if (n < 0 || k < 0) return invalid_input;
    if (k == 0 || k == n)
        return 1.0;
    if (k == 1) 
        return n;
    double res = 1.0;
    if (n - k > k)
        k = n - k;
    for(int i = k + 1; i <= n; i++) 
        res = res * i;
    for(int i = 1; i < (n-k+1); i++)
        res = res/i;
    return res;
}

void search_for_numbers_with_l_1(int k, int l, int* length, int** arr, int* flag) {
    *flag = 0;
    int count;
    int num, bit, ordinal = 0;
    if ((k < 0) || (k < l) || (l < 0)) *flag = invalid_input;
    else if (k > 31) *flag = overflow;
    else{
        *length = ceil(C(k, l));
        if (*length == invalid_input) *flag = invalid_input;
        *arr = (int*)malloc(((*length) + 1)*sizeof(int));
        if (*arr == NULL) *flag = memory_allocation_error;
        int upper_bound = (1 << k) - 1;
        if (l == 0) (*arr)[ordinal] = 0;
        else if (k == l) (*arr)[ordinal] = upper_bound;
        else{
            for (int i = 1; i <upper_bound; i++) {
                count = 0;
                num = i;
                while (num) {
                    bit = num & 1;
                    if (bit == 1) count+=1;
                    num = num >> 1;
                }
                if (count == l) {
                    (*arr)[ordinal] = i;
                    ordinal+=1;
                }
            }
        }
    }
}

void search_for_numbers_with_l_consecutive_digits_1(int k, int l, int* length, int** arr, int* flag){
    *flag = 0;
    int count;
    int num, bit, bit_pred, ordinal = 0, flag_x2, count_all_1;
    if ((k < 0) || (k < l) || (l < 0)) *flag = invalid_input;
    else if (k > 31) *flag = overflow;
    else{
        *length = k - l + 1; 
        *arr = (int*)malloc(((*length) + 1)*sizeof(int));
        if (*arr == NULL) *flag = memory_allocation_error;
        int upper_bound = (1 << k) - 1;
        if (l == 0) {
            *length = 1;
            (*arr)[ordinal] = 0;
        }
        else if (k == l) (*arr)[ordinal] = upper_bound;
        else{
            for (int i = 1; i <upper_bound; i++) {
                bit_pred = 0;
                count_all_1 = 0;
                count = 1;
                num = i;
                while (num) {
                    bit = num & 1;
                    if ((bit == 1) && (bit_pred == 1)) {
                        count+=1;
                    }
                    if (bit == 1) count_all_1+=1;
                    bit_pred = bit;
                    num = num >> 1;
                }
                if (count == l && count_all_1 == l) {
                    (*arr)[ordinal] = i;
                    ordinal+=1;
                }
            }
        }
    }
}


int print_arr(int* arr, int length) {
    if (length < 0) return error; 
    for (int i = 0; i < length; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    //free(arr);
    return success;
}

int main() {
    int l, k, length, flag;
    int* arr = NULL;
    printf("Enter how many bits will be in the numbers: k = ");
    if (scanf("%d", &k) != 1) {
        printf("Invalid input\n");
        return invalid_input;
    }
    if (k > 31) {
        printf("Overflow\n");
        return overflow;
    }
    if (k <= 0) {
        printf("The number must be positive\n");
        return invalid_input;
    }
    printf("Enter the number of digit 1: l = ");
    if (scanf("%d", &l) != 1) {
        printf("Invalid input\n");
        return invalid_input;
    }
    if (l < 0) {
        printf("The number must be non - negative\n");
        return invalid_input;
    }
    if (l > k) {
        printf("l must be less than or equal to k\n");
        return invalid_input;
    }
    int choice;
    printf("Enter 1 or 2\n1. Реализовать функцию поиска всех k-битных целых чисел типа int, в двоичной записи которых присутствует ровно l единиц(l<=k)\n2. Реализовать функцию поиска всех k-битных целых чисел типа int, в двоичной записи которых присутствует ровно l подряд идущих единиц(l<=k)\n");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        return invalid_input;
    }
    if (choice != 1 && choice != 2) {
        printf("You need to enter 1 or 2\n");
        return invalid_input;
    }
    if (choice == 1) search_for_numbers_with_l_1(k, l, &length, &arr, &flag);
    if (choice == 2) search_for_numbers_with_l_consecutive_digits_1(k, l, &length, &arr, &flag); 
    if (flag ==invalid_input) {
        printf("Invalid input\n");
        return invalid_input;
    }
    if (flag == overflow) {
        printf("Overflow\n");
        return overflow;
    }
    if (flag == memory_allocation_error) {
        printf("Memory allocation error\n");
        return memory_allocation_error;
    }
    printf("Array length: %d\n", length);
    int res;
    res = print_arr(arr, length);
    if (res == error) {
        printf("Error\n");
        return error;
    }
    if (res == success) printf("The array was successfully printed\n");
    free(arr);
    return success;
}
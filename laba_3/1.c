#include <stdio.h>
#include <stdlib.h>
#define memory_allocation_error -1
#define incorrectly_entered_values -2
#define input_error -3
#define error -4
#define success 0
#define size 32
#include <math.h>

int convert(long number, int r, long* res, int* i, int* flag) {
    if ((long)number != number) {
        free(res);
        return incorrectly_entered_values;
    }
    if ((r < 1) || (r > 5)) {
        free(res);
        return incorrectly_entered_values;
    }
    *i = 0;
    *flag = 1;
    if (number == 0) *i = 1;
    if (number < 0) {
        number = -number;
        *flag = -1;
    }
    int base = pow(2, r);
    int base_1 = base - 1;
    while (number) {
        if (number < base) {
            res[*i] = number;
        }else{
            res[*i] = number & base_1;
        }
        number = number >> r;
        printf("number & r = %d\n", number & r);
        *i = *i + 1;
    }
    return success;
}

int print(long* res, int count, int flag) {
    if (count <= 0) {
        free(res);
        return error;
    }
    if (flag == -1) printf("-");
    for (int i = count-1; i >= 0; i--) {
        printf("%d", res[i]);
    }
    printf("\n");
    return success;
}

int main() {
    int number, r, count, flag;
    printf("Enter the number you want to convert: ");
    if (scanf("%d", &number) != 1) {
        printf("Input error\n");
        return input_error;
    }
    printf("Enter the degree of the number two: ");
    if (scanf("%d", &r) != 1) {
        printf("Input error\n");
        return input_error;
    }
    long* res = (long*)calloc(size, sizeof(long));
    if (res == NULL) {
        printf("Memory allocation error\n");
        return memory_allocation_error;
    }
    int result;
    result = convert(number, r, res, &count, &flag);
    if (result == incorrectly_entered_values) {
        printf("Incorrectly entered values\n");
        return incorrectly_entered_values;
    }
    if (result == success) printf("Successfully converted\n");
    result = print(res, count, flag);
    if (result == error) {
        printf("The number of digits in the number must be positive\n");
        return error;
    }
    if (result == success) printf("The result was successfully printed\n");
    return success;
}
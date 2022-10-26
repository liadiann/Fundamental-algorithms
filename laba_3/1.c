#include <stdio.h>
#include <stdlib.h>
#define memory_allocation_error -1
#define incorrectly_entered_values -2
#define input_error -3
#define error -4
#define success 0
#define size 32
#include <math.h>

int convert(long number, int r, char* res, int* i, int* flag) {
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
    if (number == 0) {
        res[*i] = 0+'0';
        *i = 1;
    }
    if (number < 0) {
        number = -number;
        *flag = -1;
    }
    int base = pow(2, r);
    int base_1 = base - 1;
    while (number) {
        if (number < base) {
            res[*i] = number < 10 ? number+'0' : number-10 + 'A';
        }else{
            int number_1 = number & base_1;
            res[*i] = number_1 < 10 ? number_1+'0' : number_1 - 10 + 'A';
        }
        number = number >> r;
        *i = *i + 1;
    }
    return success;
}

int print(char* res, int count, int flag) {
    if (count <= 0) {
        free(res);
        return error;
    }
    if (flag == -1) printf("-");
    for (int i = count-1; i >= 0; i--) {
        printf("%c", res[i]);
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
    char* res = (char*)malloc(size*sizeof(char));
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
#include <stdio.h>
#include <stdlib.h>
#define memory_allocation_error -1
#define incorrectly_entered_values -2
#define input_error -3
#define error -4
#define success 0
#define size 33

int addition(int number_1, int number_2) {
    int res = 0, carry = 0, tmp;
    res = number_1^number_2;
    carry = (number_1 & number_2) << 1;
    while (carry) {
        tmp = res;
        res = res^carry;
        carry = (tmp & carry) << 1;
    }
    return res;
}

int reverse(char* arr, char* res, int count) {
    if (count < 0) {
        free(arr);
        free(res);
        return error;
    }
    int i = -1;
    while(count >= 0) {
        i = addition(i, 1);
        res[i] = arr[count];
        count = addition(count, -1); 
    }
    return success;
}

int convert(long number, int r, char* res, int* flag) {
    if ((long)number != number) {
        return incorrectly_entered_values;
    }
    int i = -1;
    if ((r < 1) || (r > 5)) {
        free(res);
        return incorrectly_entered_values;
    }
    *flag = 1;
    int base[] ={0, 2, 4, 8, 16, 32};
    int base_1[] = {0, 1, 3, 7, 15, 31};
    char str[]="0123456789ABCDEFGHIJKLMNOPQRSTUV";
    char* arr = (char*)calloc(size, sizeof(char));
    if (arr == NULL) {
        free(arr);
        free(res);
        return memory_allocation_error;
    }
    if (number < 0) {
        number = addition(~number, 1);
        *flag = -1;
    }
    if (number == 0) {
        arr[0] = str[0];
        i = 1;
    }else{
        while (number) {
            i = addition(i, 1);
            if (number < base[r]) {
                arr[i] = str[number];
                 i = addition(i, 1);
               
            }else{
                int number_1 = number & base_1[r];
                arr[i] = str[number_1];
            }
            number = number >> r;
        }
    }
    if (*flag == -1) {
        i = addition(i, 1);
        arr[i] = '-';
    }
    int result;
    result = reverse(arr, res, i);
    if (result == error) {
        free(arr);
        free(res);
        return error;
    }
    free(arr);
    return i;
}

int print(char* res, int count, int flag) {
    if (count <= 0) {
        free(res);
        return error;
    }
    for (int i = 0; i <= count; i++) {
        printf("%c", res[i]);
    }
    printf("\n");
    free(res);
    return success;
}

int main() {
    int number, r, flag;
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
    char* res =(char*)malloc(size*sizeof(char));
    int result;
    result = convert(number, r, res, &flag);
    if (result == incorrectly_entered_values) {
        printf("Incorrectly entered values\n");
        return incorrectly_entered_values;
    }
    if (result > 0) {
        printf("Successfully converted\n");
        
    }
    result = print(res, result, flag);
    if (result == error) {
        printf("The number of digits in the number must be positive\n");
        return error;
    }
    if (result == success) printf("The result was successfully printed\n");
    return success;
}
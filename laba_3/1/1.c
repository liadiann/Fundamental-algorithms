#include <stdio.h>
#include <stdlib.h>
#define memory_allocation_error -1
#define incorrectly_entered_values -2
#define input_error -3
#define error -4
#define success 0

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

int logarithm(int number, int r){
    if ((r < 1) || (r > 5)) return incorrectly_entered_values;
    if (((long long)number != number) || (number < 0)) return incorrectly_entered_values;
    int start = 1, count = 1;
    while(start < number){
        count = addition(count, 1);
        start = start << r;
    }
    return count;
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

int convert(long number, int r, char* res, int count) {
    if ((long long)number != number) {
        return incorrectly_entered_values;
    }
    int i = -1;
    if ((r < 1) || (r > 5)) {
        free(res);
        return incorrectly_entered_values;
    }
    if (count <= 0) return incorrectly_entered_values;
    if (res == NULL) return memory_allocation_error;
    int flag = 1;
    int base[] ={0, 2, 4, 8, 16, 32};
    int base_1[] = {0, 1, 3, 7, 15, 31};
    char str[]="0123456789ABCDEFGHIJKLMNOPQRSTUV";
    if (number < 0) {
        number = addition(~number, 1);
        flag = -1;
    }
    char* arr = (char*)calloc(count, sizeof(char));
    if (arr == NULL) {
        free(arr);
        free(res);
        return memory_allocation_error;
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
    if (flag == -1) {
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

int print(char* res, int count) {
    if (res == NULL) return memory_allocation_error;
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
    long number;
    int  r;
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
    int count;
    if (number < 0) {
        count = logarithm(addition(~number, 1), r);
        if (count == incorrectly_entered_values) {
            printf("Incorrectly entered values\n");
            return incorrectly_entered_values;
        }
        count = addition(count, 2);
    }
    if (number >= 0) {
        count = logarithm(number, r);
        if (count == incorrectly_entered_values) {
            printf("Incorrectly entered values\n");
            return incorrectly_entered_values;
        }
        count = addition(count, 1);
    }
    char* res =(char*)calloc(count, sizeof(char));
    int result;
    result = convert(number, r, res, count);
    if (result == incorrectly_entered_values) {
        printf("Incorrectly entered values\n");
        return incorrectly_entered_values;
    }
    if (result > 0) {
        printf("Successfully converted\n");
    }
    if (result == memory_allocation_error) {
        printf("Memory allocation error\n");
        return memory_allocation_error;
    }
    result = print(res, result);
    if (result == error) {
        printf("The number of digits in the number must be positive\n");
        return error;
    }
    if (result == memory_allocation_error) {
        printf("Memory allocation error\n");
        return memory_allocation_error;
    }
    if (result == success) printf("The result was successfully printed\n");
    return success;
}
#include <stdio.h>
#include <string.h>
#define input_error -1
#define error -2
#define success 0
#define SIZE 34

int isdigit_x2(char c) {
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int isalpha_x2(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;
    return 0;
}

int conversion_in_number(char number[SIZE], int base, int flag){
    if (base < 2 || base > 36) return error;
    char* ch = number - 1;
    int res = 0;
    if (flag == -1) ch++;
    while(*++ch){
        if ((isdigit_x2(*ch) && (*ch -'0' > base)) || (isalpha_x2(*ch) && (*ch - 'A' + 10 > base))){ 
            return input_error;
        }
        if (isdigit_x2(*ch)) {
                res = res * base + *ch - '0';
        }else if (isalpha_x2(*ch)){
            res = res * base + *ch - 'A' + 10;
        }else{
            return error;
        }
    }
    return res;
}

int conversion_to_number_in_other_number_systems(char str[SIZE], int number, int base, int size, int* len){
    if (base < 2 || base > 36) return input_error;
    if (size <= 0) return input_error;
    *len = 0;
    if (number == 0){
        str[0] = 0 +'0';
        (*len)++;
    }else{
        int res;
        int j = 0;
        while (number) {
            (*len)++;
            res = number % base;
            if (res > 9)
                str[j] = res - 10 + 'A';
            else
                str[j] = res + '0';
            number /= base;
            j++;
        }
    }
    return success;
}

int main() {
    int base;
    int max_number_10 = 0;
    int flag = 0;
    int flag_2 = 1;
    int res = 0;
    int size = 0;
    int len;
    char number[SIZE];
    char max_number[SIZE];
    char str[SIZE];
    printf("Enter the base of the number system: ");
    flag = scanf("%d", &base);
    if ((flag != 1) || (base < 2 || base > 36)){
        printf("Error\n");
        return input_error;
    }
    printf("Enter numbers:\n");
    while (strcmp(number, "Stop")) {
        scanf("%s", number);
        flag_2 = 1;
        if (strcmp(number, "Stop") == 0) break;
        if (number[0] == '-') flag_2 = -1;
        res = conversion_in_number(number, base, flag_2);
        if (res == error){
            printf("Error\n");
            return error;
        }
        if (res == input_error){
            printf("Input error\n");
            return input_error;
        }
        if (res >= max_number_10) {
            max_number_10 = res;
            strcpy(max_number, number);
        }
    }
    size = strlen(max_number);
    int unsigned_max = max_number_10;
    printf("Max number in %d system: %s\n", base, max_number);
    if (flag_2 == 1){
        printf("In decimal number system: %d\n", max_number_10);
    }else if (flag_2 == -1){
        size--;
        max_number_10 = flag_2 * max_number_10;
        printf("In decimal number system: %d\n", max_number_10);
    }
    printf("base = 9 : number = ");
    flag = conversion_to_number_in_other_number_systems(str, unsigned_max, 9, size, &len);
    if (flag == input_error){
        printf("Input error\n");
        return input_error;
    }
    if (flag_2 == -1) printf("-");
    for(int i = len - 1; i >= 0; i--){
        printf("%c", str[i]);
    }
    printf("\n");
    printf("base = 18 : number = ");
    if (flag_2 == -1) printf("-");
    flag = conversion_to_number_in_other_number_systems(str, unsigned_max, 18, size, &len);
    if (flag == input_error){
        printf("Input error\n");
        return input_error;
    }
    for(int i = len - 1; i >= 0; i--){
        printf("%c", str[i]);
    }
    printf("\n");
    printf("base = 27 : number = ");
    if (flag_2 == -1) printf("-");
    flag = conversion_to_number_in_other_number_systems(str, unsigned_max, 27, size, &len);
    if (flag == input_error){
        printf("Input error\n");
        return input_error;
    }
    for(int i = len - 1; i >= 0; i--){
        printf("%c", str[i]);
    }
    printf("\n");

    printf("base = 36 : number = ");
    if (flag_2 == -1) printf("-");
    flag = conversion_to_number_in_other_number_systems(str, unsigned_max, 36, size, &len);
    if (flag == input_error){
        printf("Input error\n");
        return input_error;
    }
    for(int i = len - 1; i >= 0; i--){
        printf("%c", str[i]);
    }
    printf("\n");
    return success;
}
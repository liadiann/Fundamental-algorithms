#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define memory_allocation_error -1
#define input_error -2
#define error -3
#define success 0

char* addition_in_columns(char* element_1, char* element_2, int base){
    if (base < 2) return "input error";
    int length_1, length_2, length;
    length_1 = strlen(element_1);
    length_2 = strlen(element_2);
    if (length_1 > length_2){
        length = length_1 + 2;
    }else{
        length = length_2 + 2;
    }
    char* res = (char*)malloc(length*sizeof(char));
    if (res == NULL){
        return "error";
    }
    res[length - 1] = '\0';
    length_1 = length_1 - 1;
    length_2 = length_2 - 1;
    int in_mind = 0, addend_help_1, addend_help_2, regular_sum, ost;
    for (int i = length - 2; i >= 0; i--){
        if (length_1 >= 0){
            if (element_1[length_1]>='0' && element_1[length_1]<='9') addend_help_1 = element_1[length_1] - '0';
            if (element_1[length_1]>='A' && element_1[length_1]<='Z') addend_help_1 = element_1[length_1] - 'A'+ 10;
        }else{ 
            addend_help_1 = 0;
        }
        if (length_2 >= 0){
            if (element_2[length_2]>='0' && element_2[length_2]<='9') addend_help_2 = element_2[length_2] - '0';
            if (element_2[length_2]>='A' && element_2[length_2]<='Z') addend_help_2 = element_2[length_2] - 'A'+ 10;
        }else{ 
            addend_help_2 = 0;
        }
        regular_sum = addend_help_1 + addend_help_2 + in_mind;
        in_mind = regular_sum/base;
        ost = regular_sum % base;
        if (ost >= 0 && ost <= 9) res[i] = ost +'0';
        if (ost >= 10 && ost <= 26) res[i] = ost + 'A' - 10;
        --length_1;
        --length_2;
    }
    return res;   
}


char* sum(unsigned base, unsigned count, ...){
    char* res = "0";
    va_list element;
    va_start(element, count);
    for(int i = 0; i < count; i++) {
        res = addition_in_columns(va_arg(element, char*), res, base);
        if (!strcmp(res, "error")){
            return "memory allocation error";
        }
        if (!strcmp(res, "input error")){
            return "input error";
        }
    }
    va_end(element);
    return res;
}

int main(){
    int base = 16;
    int count = 2;
    char* result;
    result = sum(base, count, (char*)"FA34", (char*)"BC12");
    if (!strcmp(result, "memory allocation error")){
        printf("Memory allocation error\n");
        return memory_allocation_error;
    }
    if (!strcmp(result, "input error")){
        printf("Input error!\n");
        return input_error;
    }
    printf("sum = %s\n", result);
    if (count != 0) free(result);
    return success;
}
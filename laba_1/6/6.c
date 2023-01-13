/*В текстовом файле находятся числа, записанные в разных системах
счисления, при этом информация о конкретной системе счисления для
каждого числа утеряна. В файле числа разделены произвольным
количеством разделителей (разделителями могут являться символы
пробела, табуляции, переноса строки). Напишете программу, которая
для каждого числа определяет минимальную систему счисления, в
которой представление этого числа корректно, и в выходной файл
выводит число, определённую для него систему счисления и
представление этого числа в десятичной системе счисления.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define length_number 10
#define memory_allocation_error -1
#define incorrectly_entered_values -2
#define input_error -3
#define file_open_error -4
#define error -5
#define success 0

int conversion_to_decimal_notation(char* number, int base, int size) {
    if (size < 0 || size == 0) return error;
    if (base < 2) return error; 
    int n = 0, index = size;
    int tmp = 1;
    while(index-- != 0){
        n += (isdigit(number[index]) ? (number[index] - '0') : (tolower(number[index]) - 'a' + 10)) * tmp;
        tmp *= base;
    }
    return n;
}

int min_numbers_systems_and_writing_to_a_file(FILE* fin, FILE* fout) {
    int base = 2, size = 0, number, flag = 1, i = 0;
    char c, _c = 0;
    char* buf = (char*)malloc((length_number+1)*sizeof(char));
    if (buf == NULL) {
        printf("Memory allocation\n");
        return memory_allocation_error;
    }
    while(!feof(fin)){
        c = fgetc(fin);
        if (c == EOF) free(buf);
        if (isalnum(c)) {
            buf[size++] = c;
        }
        if (c == '-' && i == 0) {
            flag = -1;
        }
        i+=1;
        if (isdigit(c)) {
            if (base < c - '0') {
                base = c -'0' + 1;
            }
        }
        if (isalpha(c)){
            if (base < tolower(c) - 'a' + 10) {
                base = tolower(c) - 'a' + 11;
            }
        }
        if ((isalnum(_c)) && (c == ' ' || c == '\n' || c== '\t')) {
            buf[size] = '\0';
            number = conversion_to_decimal_notation(buf, base, size);
            if (number == error) return error;
            if (flag == -1){
                fprintf(fout, "-%s   %d  -%d\n", buf, base, number);
            }else{
                fprintf(fout, "%s   %d  %d\n", buf, base, number);
            }
            free(buf);
            base = 2;
            size = 0;
            flag = 1;
            buf = (char*)malloc(length_number*sizeof(char));
            if (buf == NULL) {
                printf("Memory allocation\n");
                return memory_allocation_error;
            }
        }
        _c = c;
        i = 0;
    }
    return success;
}


int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Usage: program file_name\n");
        return error;
    }
    FILE* fin = NULL;
    FILE* fout = NULL;
    fin = fopen(argv[1], "r");
    if (fin == NULL) {
        printf("Could not open the file\n");
        return file_open_error;
    }
    fout = fopen("output_file.txt", "w");
    if (fout == NULL) {
        printf("Could not open the file\n");
        fclose(fin);
        return file_open_error;
    }
    int res = min_numbers_systems_and_writing_to_a_file(fin, fout);
    if (res == memory_allocation_error) {
        printf("Memory allocation error\n");
        fclose(fin);
        fclose(fout);
        return memory_allocation_error;
    }
    if (res == error) {
        printf("Error!\n");
        fclose(fin);
        fclose(fout);
        return error;
    }
    fclose(fin);
    fclose(fout);
    return success;
}
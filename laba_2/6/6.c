#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int* substring_search(int count, char* s, ...) {
    FILE* fIn = NULL;
    int k, n, symb = 0, el = 0;
    char c;
    int* count_ = (int*)calloc(count, sizeof(int));
    if (count_ == NULL) {
        return count_;
    }
     if (s == "") {
        for (int j = 0; j < count; j++) count_[j] = -2;
            return count_; 
    }
    va_list file;
    va_start(file, s);
    for (int i = 0; i < count; i++) {
        k = 0;
        n = 0;
        fIn = fopen(va_arg(file, char*), "r");
        if (fIn == NULL) {
            for (int j = 0; j < count; j++) count_[j] = -1;
            return count_;
        }

        while (!feof(fIn)) {
            c = fgetc(fIn);
            if (c != '\n' && c != EOF) {
                k++;
            }
            if (s[symb] == c) {
                n++;
                symb++;
            }else if (s[symb] != c) {
                n = 0;
                symb = 0;
            }
            if (n == strlen(s)) {
                count_[el] = k - n + 1;
                el++;
                break;
            }
        }
        fclose(fIn);
    }
    va_end(file);
    return count_;
}

int main() {
    char* s = " ";
    int count = 3; 
    int* res = substring_search(count, s, (char*)"txt1", (char*)"txt2", (char*)"txt3");
    if (res == NULL) {
        printf("Память не выделилась!\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        if (res[i] == -2) {
            printf("Пустая строка!\n");
            return 2;
        }
        if (res[i] == -1) {
            printf("Файл %d не открылся\n", i+1);
        }
        if (res[i] == 0) {
            printf("В %d файле нет нужной подстроки\n", i+1);
        }
        else{
            printf("В %d файле первое вхождение подстроки произошло на %d символе\n", (i+1), res[i]);
        }
    }
    free(res);
    return 0;
}
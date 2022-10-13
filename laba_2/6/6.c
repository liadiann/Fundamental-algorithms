#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int my_strstr(char* s, FILE* fin) {
    char c;
    int k = 0, n = 0, symb = 0;
    int count_ = 0;
    if (fin == NULL) {
        count_ = -1;
        return count_;
    }
    if (!strcmp(s, "")) {
        count_ = -2;
        return count_; 
    }
    while (!feof(fin)) {
            c = fgetc(fin);
            if (c != '\n' && c != EOF) {
                k++;
            }
            if (s[symb] == c) {
                n++;
                symb++;
            }else if (s[symb] == c) {
                n = 0;
                symb = 0;
            }
            if (n == strlen(s)) {
                count_ = k - n + 1;
                break;
            }
        }
        return count_;
}

int* substring_search(int count, char* s, ...) {
    FILE* fIn = NULL;
    int* count_ = (int*)calloc(count, sizeof(int));
    if (count_ == NULL) {
        return count_;
    }
    va_list file;
    va_start(file, s);
    for (int i = 0; i < count; i++) {
        fIn = fopen(va_arg(file, char*), "r");
        count_[i] = my_strstr(s, fIn);

        fclose(fIn);
    }
    va_end(file);
    return count_;
}

int main() {
    char* s = "aranara";
    int count = 3; 
    int* res = substring_search(count, s, (char*)"txt1", (char*)"txt2", (char*)"txt3");
    if (res == NULL) {
        printf("Память не выделилась!\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
       // printf("count_ = %d\n", res[i]);
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 50

int task(FILE* fin, FILE* fout) {
    if (fin == NULL) {
        return -1;
    }
    if (fout == NULL) {
        return -1;
    }
    char buf1[SIZE], buf2[SIZE], buf3[SIZE];
    int count1 = 0, count2 = 0;
    char c, _c = 0;
    char* ptr = buf1;
     while (!feof(fin)) {
        c = fgetc(fin);
        count1++;
        if (isalnum(c)) *ptr++=c;
        if (!(isalnum(c)) && isalnum(_c)) {
            count2+=1;
            *ptr = 0;
            if (count2 == 1) {
                for (int i = 0; i < count1; i++) {
                    buf2[i] = buf1[i];
                }
                count1 = 0;
            }
            if (count2 == 2) {
                for (int i = 0; i < count1; i++) {
                    buf3[i] = buf1[i];
                }
                count1 = 0;
            }
            if (count2 == 3) {
                count2 = 0;
                count1 = 0;
                fprintf(fout, "%s   ", buf1);
                fprintf(fout, "%s   ", buf2);
                fprintf(fout, "%s   ", buf3);
                fprintf(fout, "\n");
            }
            ptr = buf1;
        }
        _c = c;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: program input_file\n");
        return 1;
    }
    FILE* fIn = NULL;
    FILE* fOut = NULL;
    char buf1[SIZE], buf2[SIZE], buf3[SIZE];
    int count1 = 0, count2 = 0;
    char c, _c = 0;
    char* ptr = buf1;
    fIn = fopen(argv[1], "r");
    fOut = fopen("out", "w");
    int flag = 1;
    flag = task(fIn, fOut);
    if (flag == -1) {
        printf("Ошибка открытия файла\n");
        return 1;
    } 
    if (flag == 0) printf("Успешно выполнено\n");
    fclose(fIn);
    fclose(fOut);
    remove(argv[1]);
    rename("out", argv[1]);
    return 0;
}

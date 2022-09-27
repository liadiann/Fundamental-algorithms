#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Exclude_Digits(FILE* fin, FILE* fout){
    if (fin == NULL) {
        return -1;
    }
    if (fout == NULL) {
        return -1;
    }
    char c;
    while (!feof(fin)) {
        c = fgetc(fin);
        if (isdigit(c)) {
            fputc(' ', fout);
        }else if (c != EOF) {
            fputc(c, fout);
        }
    }
    return 0;
}

int number_of_letters_in_a_string(FILE* fin, FILE* fout) {
    if (fin == NULL) {
        return -1;
    }
    if (fout == NULL) {
        return -1;
    }
    char c;
    int count = 0, n = 0;
    while(!feof(fin)) {
        c = fgetc(fin);
        if (isalpha(c)) {
            count++;
        }
        if ((c == EOF) || (c == '\n')) {
            n++;
            fprintf(fout, "В %d строке %d символов букв\n", n, count);
            count = 0;
        }
    }
    return 0;
}

int not_a_number_not_a_letter_not_a_space(FILE* fin, FILE* fout) {
    if (fin == NULL) {
        return -1;
    }
    if (fout == NULL) {
        return -1;
    }
    char c;
    int count = 0, n = 0;
    while(!feof(fin)) {
        c = fgetc(fin);
        if (!isalnum(c) && c!= ' ') {
            count++;
        }
        if ((c == EOF) || (c == '\n')) {
            n++;
            fprintf(fout, "В %d строке %d символов, не являющихся буквами, цифрами и пробелом\n", n, count);
            count = 0;
        }
    }
    return 0;
}

int replace_symbol_to_Aski(FILE* fin, FILE* fout) {
    if (fin == NULL) {
        return -1;
    }
    if (fout == NULL) {
        return -1;
    }
    char c;
    while (!feof(fin)) {
        c = fgetc(fin);
        if (isdigit(c)) {
            fputc(c, fout);
        }else if (c != EOF) {
            fprintf(fout, "%d", (int)c);
        }
    }
    return 0;
}

int flag_f(FILE* fin, FILE* fout) {
    if (fin == NULL) {
        return -1;
    }
    if (fout == NULL) {
        return -1;
    }
    char c;
    int count = 1, flag = 0;
    while(!feof(fin)) {
        c = fgetc(fin);
        if ((c == '\n') || (c == '\t') || (c == ' ')) {
            if (flag = 1) {
                count+=1;
                flag = 0;
            }
            fputc(c, fout);
        }else if (c != EOF) {
            if (flag == 0) flag = 1;
            if ((count % 2 == 0) && (count % 5 == 0)) {
                if (isalpha(c)) {
                    c = tolower(c);
                }
                fprintf(fout, "%d", (int)c);
            }
            else if (count % 2 == 0) {
                if (isalpha(c)) {
                    c = tolower(c);
                    fputc(c, fout);
                }else fputc(c, fout);
            }
            else if (count % 5 == 0) {
                    fprintf(fout, "%d", (int)c);
            }
            else if (!(count % 2 == 0) && (count % 5 !=0)) fputc(c, fout);
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if ((argc < 3) || (argc > 4)) {
        printf("Usage: program -(/)flag input_file\nЕсли флаг содержит символ 'n', то после 'input_file' идет 'output_file'\nФлаги: d, i, s, a, f\n");
        return 1;
    }
    if ((strcmp(argv[1], "-d") != 0) && (strcmp(argv[1], "/d") != 0) && (strcmp(argv[1], "-nd") != 0) && (strcmp(argv[1], "/nd") != 0) && (strcmp(argv[1], "-i") != 0) && (strcmp(argv[1], "/i") != 0) && (strcmp(argv[1], "-ni") != 0) && (strcmp(argv[1], "/ni") != 0) && (strcmp(argv[1], "-s") != 0) && (strcmp(argv[1], "/s") != 0) && (strcmp(argv[1], "-ns") != 0) && (strcmp(argv[1], "/ns") != 0) && (strcmp(argv[1], "-a") != 0) && (strcmp(argv[1], "/a") != 0) && (strcmp(argv[1], "-na") != 0) && (strcmp(argv[1], "/na") != 0) && (strcmp(argv[1], "-f") != 0) && (strcmp(argv[1], "/f") != 0)) {
        printf("Флаг не распознан.\n");
        return 1;
    }
    FILE* fIn = NULL;
    FILE* fOut = NULL;
    char c;
    int k;
    fIn = fopen(argv[2], "r");
   // if (fIn == NULL) {
   //     perror("Ошибка: \n");
   //     return -1;
   // }
    if ((argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][1] == 'n')) {
        if (argc != 4) {
            printf("Нет имени выходного файла\n");
            return -1;
        }
        fOut = fopen(argv[3], "w");
     //   if (fOut == NULL) {
    //        perror("Ошибка: \n");
     //       return -1;
     //   }
    }else{
        if (argc != 3) {
            printf("Должно быть 3 позиции\n");
            return -1;
        }
        char* prefix = "out_";
        int length = strlen(argv[2]) + strlen(prefix) + 1;
        char newname[length];
        strcpy(newname, prefix); //копирует prefix в newname
        strcat(newname, argv[2]); //присоединяет к newname argv[2]
        fOut = fopen(newname, "w");
      //  if (fOut == NULL) {
        //     perror("Ошибка: \n");
       //     return -1;
     //   }
    }
    if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "/d") == 0 || strcmp(argv[1], "/nd") == 0 || strcmp(argv[1], "-nd") == 0) k = 1;
    if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "/i") == 0 || strcmp(argv[1], "/ni") == 0 || strcmp(argv[1], "-ni") == 0) k = 2;
    if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "/s") == 0 || strcmp(argv[1], "/ns") == 0 || strcmp(argv[1], "-ns") == 0) k = 3;
    if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a") == 0 || strcmp(argv[1], "/na") == 0 || strcmp(argv[1], "-na") == 0) k = 4;
    if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0 || strcmp(argv[1], "/nf") == 0 || strcmp(argv[1], "-nf") == 0) k = 5;
    switch (k)
    {
    case 1: ;
        int flag;
        flag = Exclude_Digits(fIn, fOut);
        if (flag == -1) {
            perror("Ошибка открытия файла");
        }
        if (flag == 0) {
            printf("Все цифры из файла исключены\n");
        }
        break;
    case 2:
        flag = number_of_letters_in_a_string(fIn, fOut);
        if (flag == -1) {
            perror("Ошибка открытия файла");
        }
        if (flag == 0) {
            printf("Символы букв в каждой строке подсчитаны\n");
        }
        break;
    case 3:
        flag = not_a_number_not_a_letter_not_a_space(fIn, fOut);
        if (flag == -1) {
            perror("Ошибка открытия файла");
        }
        if (flag == 0) {
            printf("Символы, не являющиеся буквами, цифрами и пробелом подсчитаны\n");
        }
        break;
    case 4:
        flag = replace_symbol_to_Aski(fIn, fOut);
        if (flag == -1) {
            perror("Ошибка: ");
        }
        if (flag == 0) {
            printf("Символы, не являющиеся цифрами заменены их строковым представлением Аски кода\n");
        }
        break;
    case 5:
        flag = flag_f(fIn, fOut);
        if (flag == -1) {
            perror("Ошибка открытия файла");
        }
        if (flag == 0) {
            printf("Задание успешно выполнено!\n");
        }
        break;
    }
    return 0;
}
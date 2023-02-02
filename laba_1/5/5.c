#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define incorrectly_entered_values -2
#define input_error -3
#define file_error -4
#define error -5
#define success 0
#define N 4
#define max_len_file 100

void in_file(FILE* file, char filenames[][max_len_file]) {
    for (int i = 0; i < N; i++){
        fscanf(file, "%s", filenames[i]);
    }
    fclose(file);
}

int cin(char filenames[][max_len_file]) {
    int flag = 1;
    for (int i = 0; i < N; i++){
        flag = scanf("%s", filenames[i]);
        if (flag != 1) return error;
    }
    return success;
}

void arg(char* argv[], char filenames[][max_len_file]) {
    for (int i = 2; i < N + 2; i++) {
        strcpy(filenames[i-2], argv[i]);
    }
}

bool while_files_are_open(bool* check) {
    for (int i = 0; i < N; i++) {
        if (check[i] == true) {
            return true;
        }
    }
    return false;
}

int write(FILE* fout, char filenames[][max_len_file]) {
    FILE* files[N];
    bool flag[N];
    char c;
    for (int i = 0; i < N; i++) {
        files[i] = NULL;
        flag[i] = true;
    }
    while (while_files_are_open(flag)) {
        for (int i = 0; i < N; i++) {
            if (files[i] == NULL) {
                files[i] = fopen(filenames[i], "r");
                if (files[i] == NULL) {
                    fclose(fout);
                    for (int j = 0; j < i; j++){
                        fclose(files[j]);
                    }
                    return file_error;
                }
            }
            c = getc(files[i]);
            if (c == EOF) {
                fclose(files[i]);
                flag[i] = false;
            }else {
                putc(c, fout);
            }
        }
    }
    fclose(fout);
    return success;
}

int main(int argc, char* argv[]) {
    FILE *fin = NULL;
    FILE *fout = NULL;
    int flag = 0;
    fout = fopen("file_out.txt", "w");
    if (fout == NULL){
        printf("File didn't open\n");
        return file_error;
    }
    char filename[N][max_len_file];
    if (argc == 1) {
        printf("Usage:\n1) program -fi file_name.\n2) program -cin.\n3) program -arg ...\n");
        return input_error;
    }
    if (strcmp(argv[1], "-fi") == 0) {
        if ((argc == 2) || (argc > 3)) {
            printf("Usage: program -fi file_name.\n");
            return input_error;
        }
        fin = fopen(argv[2], "r");
        if (fin == NULL) {
            printf("File didn't open\n");
            return file_error;
        }
        in_file(fin, filename);
        flag = write(fout, filename);
        if (flag == error){
            printf("Error\n");
            return error;
        }
        return success;
    }else if (strcmp(argv[1], "-cin") == 0) {
        if (argc != 2) {
            printf("Usage: program -cin\n");
            return input_error;
        }
        printf("Enter file names:\n");
        flag = cin(filename);
        if (flag == error){
            printf("Error\n");
            return error;
        }
        flag = 0;
        flag = write(fout, filename);
        if (flag == error){
            printf("Error\n");
            return error;
        }
        return success;

    } else if (strcmp(argv[1], "-arg") == 0) {
        if (argc == 2) {
            printf("Usage: program -arg ...(file names)\n");
            return input_error;
        }
        arg(argv, filename);
        flag = write(fout, filename);
        if (flag == error){
            printf("Error\n");
            return error;
        }
        return success;
    } else {
        printf("Wrong argument\n");
        return input_error;
    }
}
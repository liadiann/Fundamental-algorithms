#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void string_length(char* c, int* l) {
    char* ptr = c;
    while (*ptr) {
        *l = *l + 1;
        ptr++;
    }    
}

void reverce(char* c) {
    int l = strlen(c);
    char* ptr1 = c;
    char* ptr2 = c + l - 1;
    char tmp;
    while(ptr1 < ptr2) {
        tmp = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = tmp;
        ptr1++;
        ptr2--;
    }
}

void conversion_to_uppercase(char* c) {
    int i = 0;
    char* p = c;
    while(*p != 0) {
        if (i & 1 == 1) {
            *p = toupper(*p);
        }
        p++;
        i++;
    }
}

void flag_n(char* c, char* q) {
    int l = strlen(c);
    int count = 0;
    char* p = c;
    for (int i = 0; i < l; i++) {
        if (isdigit(*p)) {
            q[count] = *p;
            count++;
        }
        p++;
    }
    p = c;
    for (int i = 0; i < l; i++) {
        if (isalpha(*p)) {
            q[count] = *p;
            count++;
        }
        p++;
    }
    p = c;
    for (int i = 0; i < l; i++) {
        if (!isalnum(*p)) {
            q[count] = *p;
            count++;
        }
        p++;
    }
    count--;
}

void strcat2(char* c, char* q) {
    while(*c) c++;
    while(*c++ = *q++);
    c--;
}

void print_string(char* c) {
    char* p = c;
    while(*p != 0) {
        printf("%c", *p++);
    }
}

int main(int argc, char* argv[]) {
    if ((argc != 3) && (argc != 4)) {
        printf("Usage: program string1 -flag (string2 if flag -c)\nFlag: l, r, u, n, c\n");
        return 1;
    }
    if ((strcmp(argv[2], "-l") != 0) && (strcmp(argv[2], "-r") != 0) && (strcmp(argv[2], "-u") != 0) && (strcmp(argv[2], "-n") != 0) && (strcmp(argv[2], "-c") != 0)) {
        printf("Флаг не распознан.\n");
        return 1;
    }
    int k, l = 0;
    char* s;
    char* q;
    if (strcmp(argv[2], "-n") == 0) {
        q = (char*)malloc((strlen(argv[1])+1)*sizeof(char));
        if (q == NULL) {
            printf("Ошибка!\n");
            return 1;
        }
    }
    if (strcmp(argv[2], "-c") == 0 && argc != 4) {
        printf("Должен быть еще один аргумент\n");
        return 1;
    } 
    if (argc == 4) {
        int length = 0;
        string_length(argv[1], &length);
        string_length(argv[2], &length);
        s = (char*)malloc(length*sizeof(char));
        if (s == NULL) {
        printf("Ошибка!\n");
        return 1;
        }
        s = argv[1];
    }
    if (strcmp(argv[2], "-l") == 0)  k = 1;
    if (strcmp(argv[2], "-r") == 0)  k = 2;
    if (strcmp(argv[2], "-u") == 0)  k = 3;
    if (strcmp(argv[2], "-n") == 0)  k = 4;
    if (strcmp(argv[2], "-c") == 0)  k = 5;
    switch (k)
    {
    case 1:
        string_length(argv[1], &l);
        printf("Длина строки: %d\n", l);
        break;
    case 2:
        reverce(argv[1]);
        print_string(argv[1]);
        break;
    case 3:
        conversion_to_uppercase(argv[1]);
        print_string(argv[1]);
        break;
    case 4:
        flag_n(argv[1], q);
        print_string(q);
        break;
    case 5:
        strcat2(s, argv[3]);
        print_string(s);
        break;
    }
    return 0;
}
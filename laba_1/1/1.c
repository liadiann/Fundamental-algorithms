#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

void usage() {
    printf("Usage: program positive_integer -flag(or /flag)\n");
    printf("Flag: h, p, s, e, a, f\n");
}

int main(int argc, char* argv[])
{
    int k = 0; //k как счетчик
    if (argc!=3) {  //проверка
        usage();
        return 1;
    }
    char* c = argv[1];
    for (int i = 0; i < strlen(c); i++) { 
        if (isdigit(c[i]))
            k++; 
    }
    if (k != strlen(c)) {   //проверка
        usage();
        return 1;
    }
    unsigned long long N = 0;
    for (int i = 0; c[i] !='\0'; i++) { //Собираем число
        N = N * 10 + (c[i] - '0');
    }
    unsigned int n = N;
    if (n == 0) {
        printf("Число должно быть положительным\n");
        return 1;
    }
    k = 0; //k как аргумент switch
    if ((strcmp(argv[2], "-h") != 0) && (strcmp(argv[2], "/h") != 0) && (strcmp(argv[2], "-p") != 0) && (strcmp(argv[2], "/p") != 0) && (strcmp(argv[2], "-s") != 0) && (strcmp(argv[2], "/s") != 0) && (strcmp(argv[2], "-e") != 0) && (strcmp(argv[2], "/e") != 0) && (strcmp(argv[2], "-a") != 0) && (strcmp(argv[2], "/a") != 0) && (strcmp(argv[2], "-f") != 0) && (strcmp(argv[2], "/f") != 0)) {
        printf("Флаг не распознан.\n");
        usage();
        return 1;
    }
    if ((unsigned long long)n != N) {
        printf("Переполнение\n");
        return 1;
    }
    
    if ((strcmp(argv[2], "-h") == 0) || (strcmp(argv[2], "/h") == 0)) k = 1;
    if ((strcmp(argv[2], "-p") == 0) || (strcmp(argv[2], "/p") == 0)) k = 2;
    if ((strcmp(argv[2], "-s") == 0) || (strcmp(argv[2], "/s") == 0)) k = 3;
    if ((strcmp(argv[2], "-e") == 0) || (strcmp(argv[2], "/e") == 0)) k = 4;
    if ((strcmp(argv[2], "-a") == 0) || (strcmp(argv[2], "/a") == 0)) k = 5;
    if ((strcmp(argv[2], "-f") == 0) || (strcmp(argv[2], "/f") == 0)) k = 6;
    switch (k)
    {
    case 1:
        if (n > 100) {
            printf("Нет чисел в пределах 100, кратных введенному числу\n");
        }
        else{
            for (int i = 1; i <= 100; i++) {
                if ((i % n) == 0) printf("%d;", i);
            }
            printf("\n");
        }
        break;
    case 2: ;
        int count = 0;
        for (int i = 2; i < n; i++) {
            if ((n % i) == 0) count++;
        }
        if (n == 1) count = 1;
        if (count == 0) {
            printf("Введенное число является простым\n");
        }else{
            printf("Введенное число является составным\n");
        }
        break;
    case 3:
        for (int i = 0; i < strlen(c); i++) {
        printf("%c ", c[i]);
        }
        printf("\n");
        break;
    case 4: ;
        unsigned long long p;
        if (n > 10) {
            printf("Число должно быть не больше 10\n");
        }else{
            printf("1\n");
            for (int i = 2; i <= 10; i++) {
                p = 1;
                for (int j = 1; j <= n; j++) {
                    p = p * i;
                    printf("%llu ", p);
                }
            printf("\n");
           }
        }
        break;
    case 5: ;
        unsigned long long sum = 0;
        for (int i = 1; i <= n; i++) {
            sum = sum + i;
        }
        printf("sum = %llu\n", sum);
        break;
    case 6: ;
        unsigned long long f = 1;
        for (int i = 1; i <= n; i++) {
            if (n > 20) {
                printf("Произошло переполнение\n");
                return 1;
            }else{
            f = f * i;
            }
        }
        printf("factorial = %llu\n", f);
        break;
    }
    return 0;
}
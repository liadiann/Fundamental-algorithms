#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void usage() {
    printf("Usage: program positive_integer -flag(or /flag)\n");
    printf("Flag: h, p, s, e, a, f\n");
}

int multiple(int n) {
    if (n == 0) return -1; 
    for (int i = 1; i <= 100; i++) {
        if ((i % n) == 0) printf("%d;", i);
    }
}

int primality(int n) {
    int count = 0;
    if (n == 1) count = 1;
    if (n & 1 == 0) {
        count = 1;
    }else{
        for (int i = 3; i < floor(sqrt(n)); i+=2) {
            if ((n % i) == 0) count = 1;
        }
    }
    return count;
}

void split(char* c){
    char* p = c;
    while(*p != 0) {
        printf("%c ", *p++);
    }
}

void flag_e(int n){
    unsigned long long p;
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

void sum(int n) {
    unsigned long long sum = 0;
    sum = (n*(n+1))/2;
    printf("sum = %llu\n", sum);
}

double factorial(int n) {
    double f = 1.0;
    for (int i = 1; i <= n; i++) {
        
            f = f * i;
            

    }
    return f;
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
    case 1: ;
    int p;
        if (n > 100) {
            printf("Нет чисел в пределах 100, кратных введенному числу\n");
        }
        else{
            p = multiple(n);
            if (p == -1) { 
                printf("Введенное число - ноль!\n");
                return 1;
            }
            printf("\n");
        }
        break;
    case 2:
        p = primality(n);
        if (p == 0) {
            printf("Введенное число является простым\n");
        }else{
            printf("Введенное число является составным\n");
        }
        break;
    case 3:
        split(c);
        printf("\n");
        break;
    case 4:
        if (n > 10) {
            printf("Число должно быть не больше 10\n");
        }else{
            flag_e(n);
        }
        break;
    case 5:
        sum(n);
        break;
    case 6: ;
        double f = factorial(n);
        if (f == -1) {
            printf("Переполнение\n");
            return 1;
        }
        printf("factorial = %.0lf\n", f);
        break;
    }
    return 0;
}
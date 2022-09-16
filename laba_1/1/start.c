#include <stdio.h>
#include <string.h>
#include <ctype.h>

void usage() {
    printf("Usage: ./a.out positive_integer -flag(or /flag)\n");
    printf("Flag: h, p, s, e, a, f");
}

void pow(int a) {
    unsigned long long m;
    for (int i = 2; i <= 10; i++) {
        m = i;
        for (int j = 1; j <= a; j++) {
            m = m * i;
            printf("%d ", m);
        }
    printf("\n");
    }
}

int main(int argc, char** argv)
{
    int k = 0; //k как счетчик
    if (argc!=3) {  //проверка
        usage();
        return 1;
    }
    char* c = argv[1];
    unsigned long long N =(unsigned long long) argv[1];
    unsigned int n = N;

    for (int i = 0; i < strlen(c); i++) {
        if (isdigit(c[i]))
            k++; 
    }
    if (k != strlen(c)) {   //проверка
        //printf("На месте первого аргумента должно быть целое положительное число\n")
        usage();
        return 1;
    }
    k = 0; //k как аргумент switch
    if ((argv[2] != '-h') || (argv[2] != '/h') || (argv[2] != '-p') || (argv[2] != '/p') || (argv[2] != '-s') || (argv[2] != '/s') || (argv[2] != '-e') || (argv[2] != '/e') || (argv[2] != '-a') || (argv[2] != '/a') || (argv[2] != '-f') || (argv[2] != '/f')) {
        printf("Флаг не распознан.\n");
        usage();
        return 1;
    }
    if ((unsigned long long)n != N) {
        printf("Переполнение\n");
        return 1;
    }
    
    if ((argv[2] == '-h') || (argv[2] == '/h')) k = 1;
    if ((argv[2] == '-p') || (argv[2] == '/p')) k = 2;
    if ((argv[2] == '-s') || (argv[2] == '/s')) k = 3;
    if ((argv[2] == '-e') || (argv[2] == '/e')) k = 4;
    if ((argv[2] == '-a') || (argv[2] == '/a')) k = 5;
    if ((argv[2] == '-f') || (argv[2] == '/f')) k = 6;
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
    case 2:
        int count = 0;
        for (int i = 2; i < n; i++) {
            if ((n % i) == 0) count++;
        }
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
    case 4:
        if (n > 10) {
            printf("Число должно быть не больше 10\n");
        }else{
            printf("1\n");

        }
        break;
    case 5:

        break;
    case 6:

        break;
    
    }
    
}
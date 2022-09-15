#include <stdio.h>
#include <string.h>
#include <ctype.h>

void usage() {
    printf("Usage: ./a.out positive_integer -flag(or /flag)\n");
    printf("Flag:\nh - вывести в консоль числа в пределах 100, кратные введённому. Если таковых нету – вывести соответствующее сообщение;\np - определить, является ли введённое число простым или
составным;\ns - разделяет число на отдельные цифры и выводит отдельно каждую
цифру, разделяя их пробелом;\ne - вывести в консоль числа от 1 до 10, возводя их во все степени от 1
до заданного числа (для этого флага работает ограничение на
вводимое число: оно должно быть не больше 10);\na - суммирует все числа от 1 до указанного числа включительно;\nf - вычисляет факториал введенного числа\n");
}

int main(int argc, char** argv)
{
    int k = 0
    if (argc!=3) {  //проверка
        usage();
        return 1;
    }
    char* c = argv[1];
    unsigned long long N =(unsigned long long) argv[1];
    unsigned int n = N;

    for(int i = 0; i < strlen(c); i++) {
        if (isdigit(c[i]))
            k++;
    }
    if (k != strlen(c)) {   //проверка
        //printf("На месте первого аргумента должно быть целое положительное число\n")
        usage();
        return 1;
    }
    k = 0;
    if ((argv[2] != '-h') || (argv[2] != '/h') || (argv[2] != '-p') || (argv[2] != '/p') || (argv[2] != '-s') || (argv[2] != '/s') || (argv[2] != '-e') || (argv[2] != '/e') || (argv[2] != '-a') || (argv[2] != '/a') || (argv[2] != '-f') || (argv[2] != '/f')) {
        printf("Флаг не распознан.\n");
        usage();
        return 1;
    }
    if ((unsigned long long)n != N) {
        printf("Переполнение\n");
        return 1;
    }
    
}
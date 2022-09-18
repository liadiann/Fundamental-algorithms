#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

double conversion_to_number_q(char* c, int* l, int* f) {
    int k = 0;
    int count = -1;
    int sign = 1;
    double N = 0;
    f = 0;
    l = 0;
    for (int i = 0; i < strlen(c); i++) {  
        if (isdigit(c[i]))//проверка на то что символ - цифра
            k++; 
        if (c[0] == '-') {
            k++;
            sign = -1;
        }
        if ((c[i] == '.') && (c[0] !='.') && (f == 0)) {
            count++; //показатель того сколько цифр после точки
            k++;
            f = f + 1; // показатель вещественности числа
        }
        if (f == 1) count++; 
    }
    if (count == 0) k--;
    if (k != strlen(c)) {   //проверка
        printf("Введено не число\n");
        *l = 1;
        return 1;
    }else{
        for (int i = 0; c[i] !='\0'; i++) { //Собираем число
            if ((c[i] !='-') && (c[i]!='.')) {
                N = N * 10 + (c[i] - '0');
            }
        }
        if (f == 1) {
            for (int i = 0; i < count; i++) N = N/10.;
        }
        if (sign == -1) { //если число отрицательное
            N = N * sign;
            if ((N > __DBL_MAX__) || (N < __DBL_MIN__)) {
                printf("Произошло переполнение\n");
                *l = 2;
                return 1;
            }
            return N;
        }
    }
    return N;
}

double discriminant(double a, double b, double c) {
    double d;
    d = b*b-4*a*c;
    return d;
}

void flag_q(double a, double b, double c, double d) {
     double x1, x2;
     if (d < 0) printf("При a = %lf , b = %lf, c = %lf действительных корней нет\n", a, b, c);
     if (d == 0) {
        x1 = (double)(-b)/(2*a);
        printf("При a = %lf , b = %lf, c = %lf : x = %lf\n", a, b, c, x1);
    }
    if (d > 0) {
        x1 = ((double)(-b)+sqrt(d))/(2*a);
        x2 = ((double)(-b)-sqrt(d))/(2*a);
        printf("При a = %lf , b = %lf, c = %lf : x1 = %lf, x2 = %lf\n", a, b, c, x1, x2);
    }
}

int main(int argc, char* argv[]) {
    int k = 0;
    if ((strcmp(argv[1], "-q") != 0) && (strcmp(argv[1], "/q") != 0) && (strcmp(argv[1], "-m") != 0) && (strcmp(argv[1], "/m") != 0) && (strcmp(argv[1], "-t") != 0) && (strcmp(argv[1], "/t") != 0)) {
        printf("Флаг не распознан. Возможные флаги: -(/)q, -(/)m, -(/)t.\n");
        return 1;
    }
    if ((strcmp(argv[1], "-q") == 0) || (strcmp(argv[1], "/q") == 0)) k = 1;
    if ((strcmp(argv[1], "-m") == 0) || (strcmp(argv[1], "/m") == 0)) k = 2;
    if ((strcmp(argv[1], "-t") == 0) || (strcmp(argv[1], "/t") == 0)) k = 3;
    switch (k)
    {
    case 1: ;
        int l, f;
        double a, b, c, d, x;
        if (argc!=5) {
            printf("Вместе с ключом -(/)q нужно ввести 3 параметра\n");
        }else{
            a = conversion_to_number_q(argv[2], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            b = conversion_to_number_q(argv[3], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            c = conversion_to_number_q(argv[4], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if ((a == 0) && (b == 0) && (c == 0)) {
                printf("x - любое действительное число\n");
                return 0;
            }
            d = discriminant(a, b, c);
            flag_q(a, b, c, d);
            d = discriminant(a, c, b);
            flag_q(a, c, b, d);
            d = discriminant(b, a, c);
            flag_q(b, a, c, d);
            d = discriminant(b, c, a);
            flag_q(b, c, a, d);
            d = discriminant(c, a, b);
            flag_q(c, a, b, d);
            d = discriminant(c, b, a);
            flag_q(c, b, a, d);
        }
        break;
    case 2: ;
        int n, m, l ,f;
        double N, M;
        if (argc != 4) {
            printf("Вместе с ключом -(/)m нужно ввести 2 ненулевых целых числа\n");
        }else{
            N = conversion_to_number_q(argv[2], &l, &f); //первое число
            if (f == 1) {
                printf("Числа должны быть целые\n");
                return 1;
            }
            if (N == 0) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            n = (int)N;
            if ((l == 1) || (l == 2)) return 1;
            if ((long long)n != N) {
                printf("Переполнение!\n");
                return 1;
            }
            M = conversion_to_number_q(argv[3], &l, &f); // второе число
            if (f == 1) {
                printf("Числа должны быть целые\n");
                return 1;
            }
            if (M == 0) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            m = (int)M;
            if ((l == 1) || (l == 2)) return 1;
            if ((long long)m != M) {
                printf("Переполнение!\n");
                return 1;
            }
            if ((n % m) == 0) {
                printf("Первое число кратно второму\n");
            }else{
                printf("Первое число не кратно второму\n");
            }
        }
        break;
    case 3: ;
        int l, f;
        double a, b, c;
        if (argc!=5) {
            printf("Вместе с ключом -(/)t нужно ввести 3 параметра\n");
        }else{
            a = conversion_to_number_q(argv[2], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if (a == 0) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            b = conversion_to_number_q(argv[3], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if (b == 0) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            c = conversion_to_number_q(argv[4], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if (c == 0) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            if ((c*c == a*a + b*b) || (a*a == b*b + c*c) || (b*b == a*a + c*c)) {
                printf("Введенные значения могут быть сторонами прямоугольного треугольника\n");
            }else{
                printf("Введенные значения не могут быть сторонами прямоугольного треугольника\n");
            }
        }
        break;
    }
    return 0;
}

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

double conversion_to_number_q(char* c, int* l, int* f) {
    int k = 0;
    int count = -1;
    int sign = 1;
    double N = 0;
    *f = 0;
    *l = 0; //показатель ошибки
    for (int i = 0; i < strlen(c); i++) {  
        if (isdigit(c[i]))//проверка на то что символ - цифра
            k++; 
        if ((c[0] == '-') && (sign == 1)) {
            k++;
            sign = -1;
        }
        if ((c[i] == '.') && (c[0] !='.') && (*f == 0)) {
            count++; //показатель того сколько цифр после точки
            k++;
            *f = *f + 1; // показатель вещественности числа
        }
        if (*f == 1) count++; 
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
        if (*f == 1) {
            for (int i = 0; i < count-1; i++) N = N/10.;
        }
        if (sign == -1) { //если число отрицательное
            N = N * sign;
            if ((N > __DBL_MAX__) || (N < -__DBL_MAX__)) {
                printf("Произошло переполнение\n");
                *l = 2;
                return 1;
            }
            return N;
        }
    }
    return N;
}

void flag_q(double a, double b, double c, double* d, double* x1, double* x2) {
    double eps = 0.00001;
    *d = b*b-4*a*c;
    if (fabs(a) > eps) {
        if (fabs(*d) < eps) {
            *x1 = (double)(-b)/(2*a);
        } else if (*d > 0) {
            *x1 = ((double)(-b)+sqrt(*d))/(2*a);
            *x2 = ((double)(-b)-sqrt(*d))/(2*a);
        }
    }
}

void Print_q(double* d, double* x1, double* x2, double* a, double* b, double* c) {
    double eps = 0.00001;
    if (fabs(*a) < eps) printf("При a = 0 не квадратное уравнение\n");
    else if (fabs(*d) < eps) printf("При a = %lf , b = %lf, c = %lf: x = %lf\n", *a, *b, *c, *x1);
    else if (*d < 0) printf("При a = %lf , b = %lf, c = %lf действительных корней нет\n", *a, *b, *c);
    else if (*d > 0) printf("При a = %lf , b = %lf, c = %lf: x1 = %lf, x2 = %lf \n", *a, *b, *c, *x1, *x2);
}

int multiple(int n, int m) {
    int point = -1;
    if (m == 0) {
        point = 2;
        return point;
    }
    if ((n % m) == 0) {
        point = 0;
    }else{
       point = 1;
    }
    return point;
}

int triangle(double a, double b, double c) {
    double aa, bb,cc, eps = 0.0001;
    int point = -1;
    aa = a*a;
    bb = b*b;
    cc = c*c;
    if ((fabs(aa + bb - cc) < eps) || (fabs(bb + cc - aa) < eps) || (fabs(aa + cc - bb) < eps)) {
        point = 0;
    }else{
        point = 1;
    }
    return point;
}

int main(int argc, char* argv[]) {
    int k = 0;
    if (argc < 4) {
        printf("Usage: program -(/)flag\nПосле флага числа в зависимости от флага\nФлаги:q, m, t\n");
        return 1;
    }
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
        double a, b, c, d, x1, x2;
        if (argc!=5) {
            printf("Вместе с ключом -(/)q нужно ввести 3 параметра\n");
        }else{
            a = conversion_to_number_q(argv[2], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            b = conversion_to_number_q(argv[3], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            c = conversion_to_number_q(argv[4], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if ((b == 0) && (c == 0)) {
                printf("x - любое действительное число\n");
                return 0;
            }
            flag_q(a, b, c, &d, &x1, &x2);
            Print_q(&d, &x1, &x2, &a, &b, &c);
            flag_q(a, c, b, &d, &x1, &x2);
            Print_q(&d, &x1, &x2, &a, &c, &b);
            flag_q(b, a, c, &d, &x1, &x2);
            Print_q(&d, &x1, &x2, &b, &a, &c);
            flag_q(b, c, a, &d, &x1, &x2);
            Print_q(&d, &x1, &x2, &b, &c, &a);
            flag_q(c, a, b, &d, &x1, &x2);
            Print_q(&d, &x1, &x2, &c, &a, &b);
            flag_q(c, b, a, &d, &x1, &x2);
            Print_q(&d, &x1, &x2, &c, &b, &a);
        }
        break;
    case 2: ;
        int n, m, point;
        double N, M, eps = 0.0001;
        if (argc != 4) {
            printf("Вместе с ключом -(/)m нужно ввести 2 ненулевых целых числа\n");
        }else{
            N = conversion_to_number_q(argv[2], &l, &f); //первое число
            if (f == 1) {
                printf("Числа должны быть целые\n");
                return 1;
            }
            if (fabs(N) < eps) {
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
            if (fabs(M) < eps) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            m = (int)M;
            if ((l == 1) || (l == 2)) return 1;
            if ((long long)m != M) {
                printf("Переполнение!\n");
                return 1;
            }
            point = multiple(n, m);
            if (point == 2) {
                printf("Второе число - ноль!\n");
                return 1;
            }
            if (point == 0) printf("Первое число кратно второму\n");
            if (point == 1) printf("Первое число не кратно второму\n");
        }
        break;
    case 3: ;
        if (argc!=5) {
            printf("Вместе с ключом -(/)t нужно ввести 3 параметра\n");
        }else{
            a = conversion_to_number_q(argv[2], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if (fabs(a) < eps) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            b = conversion_to_number_q(argv[3], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if (fabs(b) < eps) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            c = conversion_to_number_q(argv[4], &l, &f);
            if ((l == 1) || (l == 2)) return 1;
            if (fabs(c) < eps) {
                printf("Числа должны быть отличны от нуля\n");
                return 1;
            }
            point = triangle(a, b, c);
            if (point == 0) {
                printf("Введенные значения могут быть сторонами прямоугольного треугольника\n");
            }else if (point == 1){
                printf("Введенные значения не могут быть сторонами прямоугольного треугольника\n");
            }
        }
        break;
    }
    return 0;
}

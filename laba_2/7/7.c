#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct apex{
    double x;
    double y;
}Apex;

int is_convex(int count, ...) {
    double eps = 0.000001;
    va_list element;
    va_start(element, count);
    double dx1, dx2, dy1, dy2, v_product;
    int sign1 = 0, sign2 = 0;
    Apex* v = (Apex*)malloc((count + 2) * sizeof(Apex));
    if (v == NULL) {
        return 1;
    }
    for(int i = 0; i < count; i++) {
        v[i] = va_arg(element, Apex);
    }
    v[count] = v[0];
    v[count + 1] = v[1];
    va_end(element);
    for (int i = 0; i < count; i++) {
        dx1 = v[i+1].x - v[i].x;
        dy1 = v[i+1].y - v[i].y;
        dx2 = v[i+2].x - v[i+1].x;
        dy2 = v[i+2].y - v[i+1].y;
        v_product = dx1 * dy2 - dy1 * dx2;
        if (v_product > eps) {
           sign1++; 
        }else if(v_product < -eps) {
            sign2++;
        }
    }
    free(v);
    if (sign1 == count || sign2 == count) {
        return 0;
    }else{
        return 2;
    }

}

double polynomial(int count, double x, int degree, ...){
    double res;
    va_list element;
    va_start(element, degree);
    res = va_arg(element, double);
    for(int i = degree; i > 0; i--) {
        res = res * x + va_arg(element, double);
    }
    va_end(element);
    return res;
}

int main() {
    int flag;
    printf("Выберите то, что хотите сделать(1 или 2)\n1. Проверить многоугольник на выпуклость\n2. Вычислить многочлен в точке\n");
    scanf("%d", &flag);
    if (flag == 1) {
        Apex polygon[] = {{0.6, 2.1}, {1.8, 3.6}, {2.2, 2.3}, {3.6, 2.4}, {3.1, 0.5}};
        int res;
        res = is_convex(4, polygon[0], polygon[1], polygon[2], polygon[3], polygon[4]);
        if (res == 1) {
            printf("Память не выделилась!\n");
            return 1;
        }
        if (res == 2) {
            printf("Многоугольник не выпуклый!\n");
        }
        if (res == 0) {
            printf("Многоугольник выпуклый!\n");
        }
    }
    if (flag == 2) {
        double x, res;
        printf("Введите точку, в которой вычисляется многочлен: ");
        scanf("%lf", &x);
        res = polynomial(5, x, 4, (double)3.2, (double)5.5, (double)10, (double)1.23, (double)-2);
        printf("Значение многочлена в точке %lf: %lf", x, res);
    }
    return 0;
}
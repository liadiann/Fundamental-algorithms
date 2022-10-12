#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return 0.1*x*x-x*log(x);
}

double dichotomy(double a, double b, int precision, double (*f)(double)) {
    /*double eps = 1.0;
    while ((1+eps/2) > 1) {
        eps = eps/2.;
    }*/
    if (precision < 0) return NAN;
    double eps = pow(10, -precision);
    double x;
    while (fabs(b - a) > eps) {
        x = (a + b)/2.;
        if (f(a)*f(x) > eps) {
            a = x;
        }else{
            b = x;
        }
    }
    return (a + b)/2.;
}

int main() {
    int precision;
    double x, a, b;
    printf("Введите границы интервала, на котором находится корень\na = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("Введите точность, с которой необходимо вычислить корень: ");
    scanf("%d", &precision);
    x = dichotomy(a, b, precision, f);
    if (isnan(x) != 0) {
        printf("Нужно ввести положительную точность\n");
        return 1;
    }
    printf("Корень уравнения: %.*lf\n", precision, x);
    return 0;
}
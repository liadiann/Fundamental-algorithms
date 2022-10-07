#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

double arg_geom(int count, ...) {
    double res = 1.0;
    va_list element;
    va_start(element, count);
    for(int i = 0; i < count; i++) {
        res*=va_arg(element, double);
    }
    va_end(element);
    if ((res < 0) && (count % 2 == 0)) {
        return NAN;
    }
    return pow(res, 1./count);
}

double pow_integer(double N, int degree) {
    if (degree == 1) {
        return N;
    }
    if (degree ==0) return 1;
    if (N == 0) return 0; 
    if (degree > 1) return N*pow_integer(N, degree-1);
    if (degree < 0){
        N = 1./ pow_integer(N, -degree);
    }
    return N;
}

int main() {
    double eps = 0.000001;
    double g = arg_geom(4, (double)-2.44, (double)6.322, (double)4.33, (double)13.565);
    if (isnan(g)!=0) {
        printf("Ошибка!\n");
    }else{
    printf("res =%lf\n", g);
    }
    double res;
    res = pow_integer((double)0, -3);
    if (isnan(res)!=0) {
        printf("Ошибка!\n");
        return 1;
    }
    printf("res = %lf\n", res);
    return 0;
}

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
    return pow(res, 1./count);
}

double pow_integer() {
    double res = 1.0;

}

int main() {

}

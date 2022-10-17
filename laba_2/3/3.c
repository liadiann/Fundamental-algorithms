#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define error_scanf 1
#define negative_precision 2
#define factorial_overflow -1
#define negative_factorial -2
#define the_borders_are_not_in_that_order -3

double e_lim(int precision){ //что-то не так?
    double element;
    if (precision == 0) {
        element = NAN;
    }
    int n = 1;
    element = pow(1 + (1./n), n);
    double element_next =  pow(1 + (1./(n+1)), (n + 1));
    double eps = pow(10, -precision);
    while (fabs(element_next - element) > eps) {
        element = element_next;
        ++n;
        element_next = pow(1 + (1./(n + 1)), (n + 1));
    }
    return element;
}

double e_row(int precision) {
    double res = 0.0;
    if (precision < 0) {
        res = NAN;
    }
    int n = 0;
    double element = 1.0;
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.49;
    while(fabs(element) > eps) {
    ++n;
    res = res + element;
    element = element * (1./n);
    }
    return res;
}

double f_e(double x) {
    return log(x) - 1;
}

double dichotomy(double a, double b, double eps, double (*f)(double)) {
    double res;
    if (b < a) res = -1;
    else {
        while (fabs(b - a) > eps) {
            res = (a + b)/2.;
            if (f(a)*f(res) > eps) {
                a = res;
            }else{
                b = res;
            }
        }
    res = (a + b)/2.;
    }
    return res;
}

double e_equation(int precision) {
    double res;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = dichotomy(0.0, 5.0, eps, f_e);
    return res;
}

int main() {
    int precision;
    int choice;
    double res;
    printf("Choose:\n1. e (lim); 2. e (Row); 3. e (Equation);\n4. pi (lim); 5. pi (Row); 6. pi (Equation);\n7. lnln2 (lim); 8. lnln2 (Row); 9. lnln2 (Equation);\n10. sqrt(2) (lim); 11. sqrt(2) (Row); 12. sqrt(2) (Equation);\n13. gamma (lim); 14. gamma (Row); 15. gamma (Equation).\n");
    if (scanf("%d", &choice) != 1) {
        printf("Error when entering an element\n");
        return error_scanf;
    }
    printf("Введите точность: ");
    if (scanf("%d", &precision) != 1) {
        printf("Error when entering an element\n");
        return error_scanf;
    }
    if (choice == 1) {
        res = e_lim(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("e = %.*lf\n", precision, res);
        printf("e = %.*lf\n", precision, exp(1));
    }
    if (choice == 2) {
        res = e_row(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("e = %.*lf\n", precision, res);
        printf("e = %.*lf\n", precision, exp(1));
    }
    if (choice == 3) {
        res = e_equation(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        double eps = 0.00001;
        if (fabs(res - 1) < eps) {
            printf("Segment boundaries are not in the correct order\n");
            return the_borders_are_not_in_that_order; 
        } 
        printf("e = %.*lf\n", precision, res);
        printf("e = %.*lf\n", precision, exp(1));
    }
    if (choice == 4) {
        
    }
    if (choice == 5) {
        
    }
    if (choice == 6) {
        
    }
    if (choice == 7) {
        
    }
    if (choice == 8) {
        
    }
    if (choice == 9) {
        
    }
    if (choice == 10) {
        
    }
    if (choice == 11) {
        
    }
    if (choice == 12) {
        
    }
    if (choice == 13) {
        
    }
    if (choice == 14) {
        
    }
    if (choice == 15) {
        
    }
}
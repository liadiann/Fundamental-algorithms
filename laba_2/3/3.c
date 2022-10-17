#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define error_scanf 1
#define negative_precision 2
#define factorial_overflow -1
#define negative_factorial -2
#define the_borders_are_not_in_that_order -3

double e_lim(int precision){ //что-то не так?
    double element;
    if (precision < 0) {
        element = NAN;
    }
    long int n = 1;
    element = pow(1 + (1./n), n);
    double element_next =  pow(1 + (1./(n+1)), (n + 1));
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while (fabs(element_next - element) > eps) {
        element = element_next;
        ++n;
        element_next = pow(1 + (1./(n + 1)), (n + 1));
    }
    return element;
}

double ln2_lim(int precision){ //что-то не так?
    double element;
    if (precision < 0) {
        element = NAN;
    }
    long int n = 1;
    element = n * (pow(2, 1./n) - 1);
    double element_next =  (n + 1) * (pow(2, 1./(n + 1)) - 1);
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while (fabs(element_next - element) > eps) {
        element = element_next;
        ++n;
        element_next = (n + 1) * (pow(2, 1./(n + 1)) - 1);
    }
    return element;
}



double e_row(int precision) {
    double res = 0.0;
    if (precision < 0) {
        res = NAN;
    }
    long int n = 0;
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

double pi_row(int precision) {
    double res = 0.0;
    if (precision < 0) {
        res = NAN;
    }
    int n = 1;
    double flag = 1;
    double element = 1.0;
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while(fabs(element) > eps) {
    ++n; 
    flag = 1;
    if (n % 2 == 0) {
        flag = -1;
    }
    res = res + element;
    element = flag/(2 * n - 1);
    if (n == INT_MAX) break;
    }
    return res*4;
}

double ln2_row(int precision) {
    double res = 0.0;
    if (precision < 0) {
        res = NAN;
    }
    int n = 1;
    double flag = 1;
    double element = 1.0;
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while(fabs(element) > eps) {
    ++n; 
    flag = 1;
    if (n % 2 == 0) {
        flag = -1;
    }
    res = res + element;
    element = flag/n;
    if (n == INT_MAX) break;
    }
    return res;
}

double f_e(double x) {
    return log(x) - 1;
}

double f_e_pr(double x) {
    return 1./x;
}

double f_pi(double x) {
    return cos(x) + 1;
}

double f_pi_pr(double x) {
    return -sin(x);
}

double f_ln2(double x) {
    return exp(x) - 2;
}

double f_ln2_pr(double x) {
    return exp(x);
}

double newton(double a, double b, double F(double), double Fpr(double), double eps) {
    double x;
    if (b < a) x = -1;
    else {
        x=(a + b)/2.;
        while (fabs(F(x)/Fpr(x)) > eps)
        {
            x = x - F(x)/Fpr(x);
        }
    }
    return x;
}

double e_equation(int precision) {
    double res;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.1, 4.5, f_e, f_e_pr, eps);
    return res;
}

double pi_equation(int precision) {
    double res;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.1, 4.5, f_pi, f_pi_pr, eps);
    return res;
}

double ln2_equation(int precision) {
    double res;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.1, 1.1, f_ln2, f_ln2_pr, eps);
    return res;
}

int main() {
    int precision;
    int choice;
    double res;
    printf("Choose:\n1. e (lim); 2. e (Row); 3. e (Equation);\n4. pi (lim); 5. pi (Row); 6. pi (Equation);\n7. ln2 (lim); 8. ln2 (Row); 9. ln2 (Equation);\n10. sqrt(2) (lim); 11. sqrt(2) (Row); 12. sqrt(2) (Equation);\n13. gamma (lim); 14. gamma (Row); 15. gamma (Equation).\n");
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
       // printf("e = %.*lf\n", precision, exp(1));
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
    }
    if (choice == 4) {
        
    }
    if (choice == 5) {
        res = pi_row(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("pi = %.*lf\n", precision, res);
        printf("pi = %.*lf\n", precision, M_PI);
    }
    if (choice == 6) {
        res = pi_equation(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        double eps = 0.00001;
        if (fabs(res - 1) < eps) {
            printf("Segment boundaries are not in the correct order\n");
            return the_borders_are_not_in_that_order; 
        } 
        printf("pi = %.*lf\n", precision, res);
        printf("pi = %.*lf\n", precision, M_PI);
    }
    if (choice == 7) {
        res = ln2_lim(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("ln2 = %.*lf\n", precision, res);
        printf("ln2 = %.*lf\n", precision, log(2));
    }
    if (choice == 8) {
        res = ln2_row(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("ln2 = %.*lf\n", precision, res);
        printf("ln2 = %.*lf\n", precision, log(2));
    }
    if (choice == 9) {
        res = ln2_equation(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        double eps = 0.00001;
        if (fabs(res - 1) < eps) {
            printf("Segment boundaries are not in the correct order\n");
            return the_borders_are_not_in_that_order; 
        } 
        printf("ln2 = %.*lf\n", precision, res);
        printf("ln2 = %.*lf\n", precision, log(2));
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
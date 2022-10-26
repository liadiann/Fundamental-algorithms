#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define error_scanf 1
#define negative_precision 2
#define negative_factorial -2
#define the_borders_are_not_in_that_order -3

double e_lim(int precision){ //что-то не так?
    double element;
    if (precision < 0) {
        element = NAN;
    }
    long int n = 1;
    element = pow(1 + (1./n), n);
    double element_1 =  pow(1 + (1./(n+1)), (n + 1));
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while (fabs(element_1 - element) > eps) {
        element = element_1;
        //++n;
        element_1 = pow(1 + (1./n), n);
        n*=2;
    }
    return element_1;
}

double pi_lim(int precision){ 
    double element;
    if (precision < 0) {
        element = NAN;
    }
    long int n = 1;
    element = 4.0;
    double element_next =  (pow(2*2*2, 4)/(2. * 24. * 24.));
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.001;
    while (fabs(element_next - element) > eps) {
        element = element_next;
        ++n;
        element_next = element * ((4. * n * (n + 1))/((2. * n + 1) * (2. * n + 1)));
    }
    return element_next;
}

double ln2_lim(int precision){ 
    double element;
    if (precision < 0) {
        element = NAN;
    }
    long int n = 1;
    element = n * (pow(2, 1./n) - 1);
    double element_1 =  (n + 1) * (pow(2, 1./(n + 1)) - 1);
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while (fabs(element_1 - element) > eps) {
        element = element_1;
        element_1 = n * (pow(2, 1./n) - 1);
        n*=2;
    }
    return element_1;
}

double sqrt2_lim(int precision){ 
    double element;
    if (precision < 0) {
        element = NAN;
    }
    long int n = 1;
    element = - 0.5;
    double element_next =  element - (element * element)/2. + 1.;
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while (fabs(element_next - element) > eps) {
        if (n > 50) break;
        element = element_next;
        element_next = element - (element * element)/2. + 1.;
        ++n;
    }
    return element_next;
}


/*double C(int n, int k)
{
    if (k > n/2) k = n - k;
    if (k == 0 || k == n)
        return 1.0;
    if (k == 1) 
        return n;
    //return C(n - 1, k - 1) * n / k;
    return C(n - 1, k) +C(n-1, k-1);
}*/


double C(int n, int k)
{
    if (k == 0 || k == n)
        return 1.0;
    if (k == 1) 
        return n;
    double res = 1.0;
    if (n - k > k)
        k = n - k;
    for(int i = k + 1; i <= n; i++) 
        res = res * i;
    for(int i = 1; i < (n-k+1); i++)
        res = res/i;
    return res;
}

double ln_factorial(int n) {
    double res = 0.0;
    double log_1;
    for (int i = 2; i <= n; i++) {
        log_1 = log(i);
        res = res + log_1;
    }
    return res;
}

double element_gamma(int n) {
    double res = 0.0;
    double element;
    int flag;
    double ln;
    for (int k = 1; k <= n; k++) {
        flag = 1;
        if (k & 1) flag = -1;
       /* if (isnan(factorial(k))!= 0) {
            res = NAN;
            break;
        }*/   
        ln = ln_factorial(k);
        element = C(n, k) *((double)flag/k) * ln;
       // printf("element при %d= %.16lf\n", n, element);
        res = res + element;
       //printf("res = %.16lf\n", res);
    }
    //printf("res при %d = %.16lf\n", n, res);
    return res;
}

double gamma_lim(int precision){ //вот здесь остановилась
    double element;
    double element_1;
    if (precision < 0) {
        element = NAN;
    }else{
        long int n = 1;
        element = element_gamma(n);
    //printf("element = %.16lf\n", element);
        element_1 =  element_gamma(n+1);
   // printf("element_1 = %.16lf\n", element_1);
        double eps = pow(10, -precision);
        if (precision == 0) eps = 0.01;
        while (fabs(element_1 - element) > eps) {
           if (n > 48) break;
            element = element_1;
             //printf("element = %.16lf\n", element);
      //  printf("n = %d\n", n);
            element_1 = element_gamma(n);
        //printf("element_1 = %16lf\n", element_1);
            if (isnan(element) != 0 || isnan(element_1)!= 0) {
                if (isnan(element)!= 0) element = element_1;
            break;
            }
            ++n;
            
        }
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
    int long long n = 1;
    double flag = 1;
    double element = 4.0;
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while((fabs(element) > eps) && (n < INT_MAX)) {
        ++n;
        flag = -1;
        if (n & 1) {
            flag = 1;
        }
        res = res + element;
        element = 4 * (flag/(2 * n - 1));
    }
    return res;
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

double sqrt2_row(int precision) {
    double res = 1.0;
    if (precision < 0) {
        res = NAN;
    }
    long long int n = 2;
    double h_element = pow(2, -n);
    double element = pow(2, h_element);
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    while(fabs(element) > eps) {
        if (n > 50) break;
        ++n; 
        res = res * element;
        h_element = pow(2, -n);
        element = pow(2, h_element);
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

double f_sqrt2(double x) {
    return x * x - 2;
}

double f_sqrt2_pr(double x) {
    return 2*x;
}

double newton(double a, double b, double F(double), double Fpr(double), double eps, int flag) {
    double x;
    int n;
    if (b < a) x = -1;
    else {
        x=(a + b)/2.;
        while (fabs(F(x)/Fpr(x)) > eps)
        {   
            if ((flag == 0) && (n > 5)) break;
            ++n;
            x = x - F(x)/Fpr(x);
        }
    }
    return x;
}

double e_equation(int precision) {
    double res;
    int flag = 1;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.1, 4.5, f_e, f_e_pr, eps, flag);
    return res;
}

double pi_equation(int precision) {
    double res;
    int flag = 1;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.1, 4.5, f_pi, f_pi_pr, eps, flag);
    return res;
}

double ln2_equation(int precision) {
    double res;
    int flag = 1;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.1, 1.1, f_ln2, f_ln2_pr, eps, flag);
    return res;
}

double sqrt2_equation(int precision) {
    double res;
    int flag = 0;
    if (precision < 0) {
        res = NAN;
    }
    double eps = pow(10, -precision);
    if (precision == 0) eps = 0.01;
    res = newton(0.6, 2.1, f_sqrt2, f_sqrt2_pr, eps, flag);
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
        if (fabs(res + 1) < eps) {
            printf("Segment boundaries are not in the correct order\n");
            return the_borders_are_not_in_that_order; 
        } 
        printf("e = %.*lf\n", precision, res);
    }
    if (choice == 4) {
        res = pi_lim(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("pi = %.*lf\n", precision, res);
        printf("pi = %.*lf\n", precision, M_PI);
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
        if (fabs(res + 1) < eps) {
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
        if (fabs(res + 1) < eps) {
            printf("Segment boundaries are not in the correct order\n");
            return the_borders_are_not_in_that_order; 
        } 
        printf("ln2 = %.*lf\n", precision, res);
        printf("ln2 = %.*lf\n", precision, log(2));
    }
    if (choice == 10) {
        res = sqrt2_lim(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("sqrt2 = %.*lf\n", precision, res);
        printf("sqrt2 = %.*lf\n", precision, sqrt(2));
    }
    if (choice == 11) {
        res = sqrt2_row(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        printf("sqrt2 = %.*lf\n", precision, res);
        printf("sqrt2 = %.*lf\n", precision, sqrt(2));
    }
    if (choice == 12) {
        res = sqrt2_equation(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        double eps = 0.00001;
        if (fabs(res + 1) < eps) {
            printf("Segment boundaries are not in the correct order\n");
            return the_borders_are_not_in_that_order; 
        } 
        printf("sqrt2 = %.*lf\n", precision, res);
        printf("sqrt2 = %.*lf\n", precision, sqrt(2));
    }
    if (choice == 13) {
        res = gamma_lim(precision);
        if (isnan(res) != 0) {
            printf("Enter positive precision\n");
            return negative_precision;
        }
        double eps = 0.00001;
        if (fabs(res + 1.0) < eps) {
            printf("Factorial of a negative number \n");
            return negative_factorial; 
        } 
        printf("gamma = %.*Lf\n", precision, res);
    }
    if (choice == 14) {
        
    }
    if (choice == 15) {
        
    }
}
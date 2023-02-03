#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define invalid_input -1
#define input_error -2 
#define memory_allocation_error -3
#define error -4
#define success 0

int create_matrix(float ***matrix, int str, int column) {
    if ((str < 1 || str > 10) && (column < 1 || column > 10)) return invalid_input;
    (*matrix) = (float**)malloc(str * sizeof(float*));
    if ((*matrix) == NULL) return memory_allocation_error;
    float number;
    for (int i = 0; i < str; i++) {
        (*matrix)[i] = (float*)malloc(column * sizeof(float));
        if ((*matrix)[i] == NULL){
            for (int k = 0; k < i; k++) free((*matrix)[k]);
            free((*matrix));
            return memory_allocation_error;
        }
        for (int j = 0; j < column; j++) {
            number = rand() % (100 + 100 + 1) - 100;
            (*matrix)[i][j] = number;
        }
    }
    return success;
}

int matrix_multiplication(float **matrix_1, float **matrix_2, float ***matrix_result, int str_1, int column_1, int str_2, int column_2, int* str_result, int* column_result) {
    (*str_result) = str_1;
    (*column_result) = column_2;
    if ((str_1 < 1 || str_1 > 10 || str_2 < 1 || str_2 > 10) && (column_1 < 1 || column_1 > 10 || column_2 < 1 || column_2 > 10)) return invalid_input;
    if (column_1 != str_2) return error;
    (*matrix_result) = (float**)malloc(str_1 * sizeof(float*));
    if ((*matrix_result) == NULL) return memory_allocation_error;
    for (int i = 0; i < str_1; i++) {
        (*matrix_result)[i] = (float*)malloc((*column_result) * sizeof(float));
        if ((*matrix_result)[i] == NULL){
            for (int k = 0; k < i; k++) free((*matrix_result)[k]);
            free((*matrix_result));
            return memory_allocation_error;
        }
        for (int j = 0; j < column_2; j++) {
            (*matrix_result)[i][j] = 0;
            for (int q = 0; q < column_1; q++) {
                (*matrix_result)[i][j] += matrix_1[i][q] * matrix_2[q][j];
            }
        }
    }
    return success;
}

int determinant(float **matrix, int str, int column, float *determinant) {
    if ((str < 1 || str > 10) && (column < 1 || column > 10)) return invalid_input;
    if (str != column) return input_error;
    if (str == 1) {
        (*determinant) = matrix[0][0];
        return success;
    }
    *determinant = 1.0;
    double eps = 0.0000001;
    float divider, help_element;
    int i;
    for (int i = 0; i < column; i++) {
        for (int j = 1 + i; j < str; j++) {
            if (!(fabsf(matrix[j][i]) < eps)) {
                divider =(float) fabsf(matrix[j][i]) / fabsf(matrix[i][i]);
                for (int q = column; q >= 0; q--) {
                    help_element = matrix[i][q] * divider;
                    if (matrix[j][i] * matrix[i][i] > eps || fabsf(matrix[j][i] * matrix[i][i]) < eps) {
                        matrix[j][q] -= help_element;
                    } else {
                        matrix[j][q] += help_element;
                    }
                }
            }
        }
        (*determinant) *= matrix[i][i];
    }
    return success;
}

int free_matrix(float ***matrix, int str) {
    if (str < 1 || str > 10) return invalid_input;
    for (int i = 0; i < str; i++) {
        free((*matrix)[i]);
    }
    free((*matrix));
    return success;
}

int print_matrix(float **matrix, int str, int column) {
    if ((str < 1 || str > 10) && (column < 1 || column > 10)) return invalid_input;
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < column; j++) {
            printf("%.6f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return success;
}

int main() {
    srand(time(NULL));
    int flag = 0;
    int str_1 = 3, str_2 = 2, column_1 = 2, column_2 = 3, str_3, column_3;
    float **matrix_1, **matrix_2, **matrix_result;
    float determinant_1, determinant_2, determinant_3;
    flag = create_matrix(&matrix_1, str_1, column_1);
    if (flag == memory_allocation_error){
        printf("Memory allocation error\n");
        return memory_allocation_error;
    }
    if (flag == invalid_input){
        printf("Error\n");
        return invalid_input;
    }
    flag = create_matrix(&matrix_2, str_2, column_2);
    if (flag == memory_allocation_error){
        printf("Memory allocation error\n");
        free_matrix(&matrix_1, str_1);
        return memory_allocation_error;
    }
    if (flag == invalid_input){
        printf("Error\n");
        free_matrix(&matrix_1, str_1);
        return invalid_input;
    }
    printf("Matrix 1:\n");
    flag = print_matrix(matrix_1, str_1, column_1);
    if (flag == invalid_input){
        printf("Error\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        return invalid_input;
    }
    printf("Matrix 2:\n");
    flag = print_matrix(matrix_2, str_2, column_2);
    if (flag == invalid_input){
        printf("Error\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        return invalid_input;
    }
    flag = matrix_multiplication(matrix_1, matrix_2, &matrix_result, str_1, column_1, str_2, column_2, &str_3, &column_3);
    if (flag == invalid_input){
        printf("Invalid input\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        return invalid_input;
    }
    if (flag == error){
        printf("You can't perfom an operation\n");
        *matrix_result == NULL;
    }
    if (flag == memory_allocation_error){
        printf("Memory allocation error\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        return memory_allocation_error;
    }
    printf("The result of matrixes multyplication:\n");
    flag = print_matrix(matrix_result, str_3, column_3);
    if (flag == invalid_input){
        printf("Error\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        free_matrix(&matrix_result, str_3);
        return invalid_input;
    }
    flag = determinant(matrix_1, str_1, column_1,&determinant_1);
    if (flag == invalid_input){
        printf("Invalid input\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        free_matrix(&matrix_result, str_3);
        return invalid_input;
    }
    if (flag == input_error){
        printf("You can't perfom an operation for matrix 1\n");
    }else{
        printf("Determinant of 1 matrix: %.6f\n", determinant_1);
    }
    flag = determinant(matrix_2, str_2, column_2, &determinant_2);
    if (flag == invalid_input){
        printf("Invalid input\n");
        free_matrix(&matrix_1, str_1);
        free_matrix(&matrix_2, str_2);
        free_matrix(&matrix_result, str_3);
        return invalid_input;
    }
    if (flag == input_error){
        printf("You can't perfom an operation for matrix 2\n");
    }else{
        printf("Determinant of 2 matrix: %.6f\n", determinant_2);
    }
    if (*matrix_result != NULL){
        flag = determinant(matrix_result, str_3, column_3, &determinant_3);
        if (flag == invalid_input){
            printf("Invalid input\n");
            free_matrix(&matrix_1, str_1);
            free_matrix(&matrix_2, str_2);
            free_matrix(&matrix_result, str_3);
            return invalid_input;
        }
        if (flag == input_error){
            printf("You can't perfom an operation for matrix result\n");
        }else{
            printf("Determinant of matrix result: %.6f\n", determinant_3);
        }
    }
    free_matrix(&matrix_1, str_1);
    free_matrix(&matrix_2, str_2);
    free_matrix(&matrix_result, str_3);
    return success;
}
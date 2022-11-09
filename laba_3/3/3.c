#include <stdio.h>
#include <stdlib.h>
#define success 0
#define invalid_input -1
#define memory_allocation_error -2
#define error -3

typedef struct employee{
    unsigned int id;
    char* name;
    char* surname;
    double salary;
}employee;

int from_file_to_array(FILE* fin, employee* arr){

}



int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: ./program.exe input_file output_file -(or /)flag(a, d)\n");
        return error;
    }
    if ((strcmp(argv[3], "-a") != 0) && (strcmp(argv[3], "/a") != 0) && (strcmp(argv[3], "-d") != 0) && (strcmp(argv[3], "/d") != 0)) {
        printf("The flag is not recognized\n");
        return error;
    }
    int k;
    if ((strcmp(argv[3], "-a") == 0) || (strcmp(argv[3], "/a") == 0)) k = 1;
    if ((strcmp(argv[3], "-d") == 0) || (strcmp(argv[3], "/d") == 0)) k = 2;

}
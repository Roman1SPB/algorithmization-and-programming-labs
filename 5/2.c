#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_int(void* a, void* b) {
    int temp = *(int*) a;
    *((int*)a) = *(int*) b;
    *((int*)b) = temp;
}

void swap_double(void* a, void* b) {
    double temp = *(double*) a;
    *((double*)a) = *(double*) b;
    *((double*)b) = temp;
}

void swap_char(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void swap_strings(void* a, void* b) {
    char* temp = *(char**)a;
    *(char**)a = *(char**)b;
    *(char**)b = temp;
}

short cmp_strings(void* a, void* b) {
    char* a_string = *(char**)a;
    char* b_string = *(char**)b;  
    
    return (strcmp(a_string, b_string) < 0) ? 0 : 1;
}

short cmp_int(void* a, void* b) {
    int a_int = *(int*) a;
    int b_int = *(int*) b;
    return (a_int < b_int) ? 0 : 1;
}

short cmp_double(void* a, void* b) {
    double a_double = *(double*) a;
    double b_double = *(double*) b;
    return (a_double < b_double) ? 0 : 1;
}

void sort(void* array, int length, int type_size, void(*swap)(void* a, void* b), short(*cmp)(void* a, void* b)) {
    for (int i = 0; i < length; i++) {
        int min_index = i;
        void* array_i = array + i*type_size;
        void* min_val = array_i;
        for (int j = i + 1; j < length; j++) {
            void* array_j = array + j*type_size;
            int cmp_result = cmp(array_j, min_val);
            if (cmp_result == 0) min_val = array_j;
        }

        swap(array_i, min_val);
    }
}

int main() {

    int nums_int[5] = {5, 6, 3, 7, 1};
    sort((void*) nums_int, 5, 4, swap_int, cmp_int);
    for (int i = 0; i < 5; i++) printf("%d ", nums_int[i]); printf("\n");

    double nums_double[7] = {7.0, 6.0, -10.0, 5.0, 4.0, 100.0, 4.5};
    sort((void*) nums_double, 7, 8, swap_double, cmp_double);
    for (int i = 0; i < 7; i++) printf("%lf ", nums_double[i]); printf("\n");

    char* strings[6] = {"576\0", "GGG\0", "BYE\0", "ABC\0", "XYZ\0", "ZXC\0"};
    sort((void **) strings, 6, sizeof(char*), swap_strings, cmp_strings);
    for (int i = 0; i < 6; i++) printf("%s ", strings[i]); printf("\n");

    return 0;
}
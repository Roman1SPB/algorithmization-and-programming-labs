#include <stdio.h>
#include <math.h>

void sort_double(void* nums, int length, int byte_size, void (*swapDouble)(void* num1, void* num2), double (*cmpDouble)(void* num1, void* num2));

double cmpDouble(void* num1, void* num2) {
    return *(double*) num1 < *(double*) num2;
}

void swapDouble(void* num1, void* num2) {
    double temp1 = *(double*) num1;
    double temp2 = *(double*) num2;
    *(double*) num1 = temp2;
    *(double*) num2 = temp1;
}

void sort_double(void* nums, int length, int byte_size, void (*swapDouble)(void* num1, void* num2), double (*cmpDouble)(void* num1, void* num2)) {
    for (int i = 0; i < length; i++) {
        int max_index = i;
        for (int j = i; j < length; j++) {
            double res1 = cmpDouble(&((double*) nums)[j], &((double*) nums)[max_index]);
            if (res1 > 0) max_index = j;
        }
        swapDouble(&((double*) nums)[i], &((double*) nums)[max_index]);
    }

    for (int i = 0; i < length; i++) {
        printf("%lf ", ((double*) nums)[i]);
    }
    printf("\n");
}

int main() {
    double b[] = {5.5, 7.5, 3.4, -1.9, 2.1, 3.4};
    int bLen = sizeof(b) / sizeof(double);
    sort_double((void*) b, bLen, sizeof(double), swapDouble, cmpDouble);

    return 0;
}
#include <stdio.h>
#include <math.h>

void sort_int(void* nums, int length, int byte_size, void (*swapInt)(void* num1, void* num2), short (*cmpInt)(void* num1, void* num2));

short cmpInt(void* num1, void* num2) {
    return *(short*) num1 < *(short*) num2;
}

void swapInt(void* num1, void* num2) {
    int temp1 = *(int*) num1;
    int temp2 = *(int*) num2;
    *(int*) num1 = temp2;
    *(int*) num2 = temp1;
}

void sort_int(void* nums, int length, int byte_size, void (*swapInt)(void* num1, void* num2), short (*cmpInt)(void* num1, void* num2)) {
    for (int i = 0; i < length; i++) {
        int max_index = i;
        for (int j = i; j < length; j++) {
            short res1 = cmpInt(&((int*) nums)[j], &((int*) nums)[max_index]);
            if (res1 > 0) max_index = j;
        }
        swapInt(&((int*) nums)[i], &((int*) nums)[max_index]);
    }

    for (int i = 0; i < length; i++) {
        printf("%d ", ((int*) nums)[i]);
    }
    printf("\n");
}

int main() {
    int a[] = {5, 7, 3, -1, 2, 3};
    int aLen = sizeof(a) / sizeof(int);
    sort_int((void*) a, aLen, sizeof(int), swapInt, cmpInt);

    return 0;
}
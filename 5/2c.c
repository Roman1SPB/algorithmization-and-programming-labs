#include <stdio.h>
#include <math.h>

void sort_str(void* nums[], int length, int byte_size, void (*swapStr)(void* num1, void* num2), int (*cmpStr)(void* num1, void* num2));

int cmpStr(void* str1, void* str2) {
    char* char_str1 = (char*) str1;
    char* char_str2 = (char*) str2;
    printf("%s %s\n", str1, str2);
    int i = 0;
    char end = '1';
    while (char_str1[i] != end && char_str2[i] != end) {
        if (char_str1[i] < char_str2[i]) return 1;
        else if (char_str1[i] > char_str2[i]) return -1;
        i++;
    }
    if (char_str1[i] == end && char_str2[i] == end) return 0;
    if (char_str2[i] == end) return -1;
    if (char_str1[i] == end) return 1;
    
    return 1;
}

void swapStr(void* str1, void* str2) {
    char** char_str1 = (char**) str1;
    char** char_str2 = (char**) str2;
    str1 = (void*) &char_str2;
    str2 = (void*) &char_str1;
}

void sort_str(void* nums[], int length, int byte_size, void (*swapStr)(void* num1, void* num2), int (*cmpStr)(void* num1, void* num2)) {
    for (int i = 0; i < length; i++) {
        int max_index = i;
        for (int j = i; j < length; j++) {
            int res1 = cmpStr(&((char**) nums)[j], &((char**) nums)[max_index]);
            if (res1 > 0) max_index = j;
        }
        swapStr(&((char*) nums)[i], &((char*) nums)[max_index]);
    }

    for (int i = 0; i < length; i++) {
        printf("%s\n", ((char**)nums)[i]);
    }
}

int main() {
    char* c[] = {"QQQ1", "SDF1", "ABC1", "MVP1", "ZXC1", "GG1"};
    // for (int i = 0; i < 6; i++) {
    //     printf("%s\n", c[i]);
    // }
    int cLen = 6;
    sort_str((void*) c, cLen, -1, swapStr, cmpStr);

    return 0;
}
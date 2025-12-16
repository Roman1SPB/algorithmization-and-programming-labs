#include <stdio.h>
const char* strng1 = "Hello\0";
const char* strng2 = "Goodbye\0";
const char* getString() {
    return strng1;
}

const char* getAnotherString() {
    return strng2;
}

int main() {
    typedef const char*(*ptr_get_strng)();
    const char*(*ptr1)() = getString;
    const char*(*ptr2)() = getAnotherString;
    ptr_get_strng array[2] = {ptr1, ptr2};
    array[0];
    array[1];

    return 0;
}
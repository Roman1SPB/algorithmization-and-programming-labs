#include <stdio.h>
#include <math.h>
typedef double(*func)(double a, double b);
const double EPS = 0.0001;

double sum(double a, double b) {return a+b;}
double sub(double a, double b) {return a-b;}
double mul(double a, double b) {return a*b;}
double div(double a, double b) {return a/b;}
double power(double a, double b) {return pow(a, b);}

void get_calculator_input();
void calculate_result(double num1, double num2, char operation);
int check_input(int scanf_check1, int scanf_check2, int scanf_check3);

void calculate_result(double num1, double num2, char operation) {
    double result = 0;
    switch(operation) {
        case '+': 
            result = sum(num1, num2);
            break;
        case '-':
            result = sub(num1, num2);
            break;
        case '*':
            result = mul(num1, num2);
            break;
        case '/':
            result = div(num1, num2);
            break;
        case '^':
            result = power(num1, num2);
            break;
        default:
            printf("Operation %c is not founded. Try +, -, *, / or ^", operation);
            return get_calculator_input(); 
    }

    printf("%lf %c %lf = %lf\n", num1, operation, num2, result);
    return get_calculator_input();
}

void get_calculator_input() {
    printf("Input: num1 num2[operation]\n");
    double num1, num2;
    char operation;
    int scanf_check1 = scanf_s("%lf", &num1);
    int scanf_check2 = scanf_s("%lf", &num2);
    int scanf_check3 = scanf_s("%c", &operation);

    int check_result = check_input(scanf_check1, scanf_check2, scanf_check3);
    if (check_result == -1) return get_calculator_input();
    else calculate_result(num1, num2, operation);
}

int check_input(int scanf_check1, int scanf_check2, int scanf_check3) {
    if (scanf_check1 == 0) {
        printf("First number is not correct. Try again!\n");
        return -1;
    }

    if (scanf_check2 == 0) {
        printf("Second number is not correct. Try again!\n");
        return -1;
    }

    if (scanf_check3 == 0) {
        printf("Operation is not correct. Try +, -, *, / or ^\n");
        return -1;
    }

    return 0;
}

int test(double(*func)(double a, double b), double argument1, double argument2, double expected_result) {
    double res = func(argument1, argument2);
    // printf("%lf %lf\n", res, expected_result);
    if (abs(res - expected_result) <= EPS) printf("Test passed!\n");
    else printf("Test failed\n");
}

void tests() {
    test(sum, 66.0, 1.0, 67.0);
    test(sub, 68.0, 1.0, 67.0);
    test(mul, 67.0/3.0, 3.0, 67.0);
    test(div, 67.0*10.0, 10.0, 67.0);
    test(power, 2.0, 20.0, 1048577.0); // Test failed. To fix we can change 1048577.0 to 1048576
}

int main() {
    void (*p_get_calculator_input)() = get_calculator_input;
    //p_get_calculator_input(); // uncomment to start calculator
    tests();
    return 0;
}
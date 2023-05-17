#include "test_pyc.h"
#include "test_multip.h"
#include <stdio.h>
#include <string.h>


int test_add(int a, int b)
{
    int c = a + b;
    printf("a = %d\r\n", a);
    printf("b = %d\r\n", b);
    printf("a + b = %d\r\n", c);
    return c;
}

void test_matrix_add(int *a, int *b, uint16_t row, uint16_t col, int *out)
{
    printf("matrix a: %d x %d\r\n", row, col);
    for(uint16_t i = 0; i < row; i++) {
        for(uint16_t j = 0; j < col; j++) {
            printf("%d ", *(a+i*col+j));
        }
        printf("\r\n");
    }

    printf("matrix b: %d x %d\r\n", row, col);
    for(uint16_t i = 0; i < row; i++) {
        for(uint16_t j = 0; j < col; j++) {
            printf("%d ", *(b+i*col+j));
        }
        printf("\r\n");
    }

    printf("matrix c = a + b: %d x %d\r\n", row, col);
    for(uint16_t i = 0; i < row; i++) {
        for(uint16_t j = 0; j < col; j++) {
            *(out+i*col+j) = *(a+i*col+j) + *(b+i*col+j);
            printf("%d ", *(out+i*col+j));
        }
        printf("\r\n");
    }
}

void test_put_str(char *str)
{
    printf("input str len: %d\r\n", strlen(str));
    printf("input str: %s\r\n", str);
}

char *test_get_str(void)
{
    char *test_string = "pyc test get string";
    printf("origin str: %s\r\n", test_string);
    return test_string;
}

float test_multipcation(float a, float b, float c)
{
    printf("a = %f\r\n", a);
    printf("b = %f\r\n", b);
    printf("c = %f\r\n", c);
    float d = test_multip_f(a, b);
    d = test_multip_f(d, c);
    printf("a*b*c = %f\r\n", d);
    return d;
}

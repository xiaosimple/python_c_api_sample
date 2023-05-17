#include "test_multip.h"
#include <stdio.h>


float test_multip_f(float a, float b)
{
    float c = a*b;
    printf("a * b = %f\r\n", c);
    return c;
}

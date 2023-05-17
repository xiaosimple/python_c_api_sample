#ifndef __TEST_PYC_H
#define __TEST_PYC_H

#include "data_type.h"

#ifdef __cplusplus
extern "C" {
#endif

int test_add(int a, int b);
void test_matrix_add(int *a, int *b, uint16_t row, uint16_t col, int *out);
void test_put_str(char *str);
char *test_get_str(void);
float test_multipcation(float a, float b, float c);

#ifdef __cplusplus
}
#endif
#endif

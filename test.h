#ifndef TEST_H
#define TEST_H

#define TESTNUM                  10000
#define T_TEST_DATA_WORD_SIZE       64
#define T_TEST_WORD_LEN_RANDOM       0
#define T_USE_RANDOM_WORD_SIZE       0

#include "dtype.h"

void bignum_add_time_test();

void bignum_sub_time_test();

void bignum_mul_time_test();

void bignum_mul_k_time_test();

void bignum_div_time_test();

void python_add_test(const char* filename, int testnum);

void python_sub_test(const char* filename, int testnum);

void python_mul_test(const char* filename, int testnum);

void python_div_test(const char* filename, int testnum);

void python_mul_k_test(const char* filename, int testnum);
#endif
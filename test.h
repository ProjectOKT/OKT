#ifndef TEST_H
#define TEST_H

#define TESTNUM                     1
#define T_TEST_DATA_WORD_SIZE       (1920/sizeof(word))
#define T_TEST_WORD_LEN_RANDOM       0
#define T_USE_RANDOM_WORD_SIZE       0
#define T_TEST_ALL_CASE              0
#include "dtype.h"

void bignum_add_time_test();

void bignum_sub_time_test();

void bignum_mul_time_test();

void bignum_mul_k_time_test();

void bignum_div_time_test();

void bignum_squ__vs_mul_time_test();

void python_add_test(const char* filename, int testnum);

void python_sub_test(const char* filename, int testnum);

void python_mul_test(const char* filename, int testnum);

void python_div_test(const char* filename, int testnum);

void python_mul_k_test(const char* filename, int testnum);

void python_squ_test(const char* filename, int testnum);

void python_squ_k_test(const char* filename, int testnum);

void python_lshift_test(const char* filename, int testnum);

void python_rshift_test(const char* filename, int testnum);

void python_squ_k_test(const char* filename, int testnum);

void python_l2r_test(const char* filename, int testnum) ;

void python_r2l_test(const char* filename, int testnum);

void python_MaS_test(const char* filename, int testnum);

void python_bar_redu_test(const char* filename, int testnum);

#endif
#ifndef TEST_H
#define TEST_H

#include "dtype.h"

#define TESTNUM                     1     //number of test case
#define TESTNUM_modexp              1      //number of test case to modexp
#define T_TEST_DATA_WORD_SIZE       (2048 / SIZEOFWORD)     //test bigint word_len

//test flags
#define T_TEST_WORD_LEN_RANDOM       0
#define T_USE_RANDOM_WORD_SIZE       0
#define T_TEST_ALL_CASE              0          //Run All case of operator bigint(ex. pp, nn, np, ..., zz)
#define T_TEST_AVERAGE               0        //Measure time with testnum average or sum

void bignum_add_time_test();

void bignum_sub_time_test();

void bignum_mul_time_test();

void bignum_mul_k_time_test();

void bignum_div_time_test();

void bignum_squ__vs_mul_time_test();

void bignum_time_all_test();

void bignum_squ_vs_squ_k_time_test();

void python_add_test(const char* filename);

void python_sub_test(const char* filename);

void python_mul_test(const char* filename);

void python_bin_div_test(const char* filename);

void python_mul_k_test(const char* filename);

void python_squ_test(const char* filename);

void python_squ_k_test(const char* filename);

void python_lshift_test(const char* filename);

void python_rshift_test(const char* filename);

void python_squ_k_test(const char* filename);

void python_l2r_test(const char* filename) ;

void python_r2l_test(const char* filename);

void python_MaS_test(const char* filename);

void python_bar_redu_test(const char* filename);

void python_word_div_test(const char* filename);

void python_naive_div_test(const char* filename);

#endif
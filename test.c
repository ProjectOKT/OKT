#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bigintfun.h"
#include "arrayfun.h"
#include "dtype.h"
#include "errormsg.h"
#include "params.h"
#include "verify.h"
#include "operation.h"
#include "test.h"
#include "rsa.h"


/**
 * @brief Runs a time test for bigint addition operation.
 *
 * This function measures the execution time of the bigint addition operation. 
 * It is used to benchmark the performance of the addition function and 
 * validate its efficiency.
 *
 * @return void
 */
void bignum_add_time_test()
{
    clock_t start, end;
    double cpu_time_used;



    bigint *pos_a = NULL;
    bigint *pos_b = NULL;
    bigint *neg_c = NULL;
    bigint *neg_d = NULL;
    bigint *pp_add = NULL;
    bigint *nn_add = NULL;
    bigint *pn_add = NULL;
    bigint *np_add = NULL;

#if T_TEST_ALL_CASE == 1
    bigint *z = NULL;
    bigint *pz_add = NULL;
    bigint *nz_add = NULL;
    bigint *zp_add = NULL;
    bigint *zn_add = NULL;
    bigint *zz_add = NULL;
#endif

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE);
#endif
        start = clock();
        bi_add(&pp_add, pos_a, pos_b);
        end = clock();
        bi_add(&nn_add, neg_c, neg_d);
        bi_add(&pn_add, pos_a, neg_d);
        bi_add(&np_add, neg_c, pos_b);
        
#if T_TEST_ALL_CASE == 1
        bi_new(&z,1);
        bi_add(&pz_add, pos_b, z);
        bi_add(&nz_add, neg_c, z);
        bi_add(&zp_add, z, pos_b);
        bi_add(&zn_add, z, neg_c);
        bi_add(&zz_add, z, z);
#endif
    }
    bi_delete(&pos_a);
    bi_delete(&pos_b);
    bi_delete(&neg_c);
    bi_delete(&neg_d);
    bi_delete(&pp_add);
    bi_delete(&nn_add);
    bi_delete(&pn_add);
    bi_delete(&np_add);

#if T_TEST_ALL_CASE == 1
    bi_delete(&z);
    bi_delete(&pz_add);
    bi_delete(&zn_add);
    bi_delete(&nz_add);
    bi_delete(&zp_add);
    bi_delete(&zz_add);
#endif
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[add] Execution time: %f seconds\n", cpu_time_used);
}


/**
 * @brief Runs a time test for bigint subtraction operation.
 *
 * This function measures the execution time of the bigint subtraction operation.
 * It is used to benchmark the performance of the subtraction function and
 * validate its efficiency.
 *
 * @return void
 */
void bignum_sub_time_test()
{
    clock_t start, end;
    double cpu_time_used;



    bigint *pos_a = NULL;
    bigint *pos_b = NULL;
    bigint *neg_c = NULL;
    bigint *neg_d = NULL;
    bigint *pp_sub = NULL;
    bigint *nn_sub = NULL;
    bigint *pn_sub = NULL;
    bigint *np_sub = NULL;

#if T_TEST_ALL_CASE == 1
    bigint *z = NULL;
    bigint *pz_sub = NULL;
    bigint *nz_sub = NULL;
    bigint *zp_sub = NULL;
    bigint *zn_sub = NULL;
    bigint *zz_sub = NULL;
#endif

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE);
#endif
        start = clock();
        bi_sub(&pp_sub, pos_a, pos_b);
        end = clock();
        bi_sub(&nn_sub, neg_c, neg_d);
        bi_sub(&pn_sub, pos_a, neg_d);
        bi_sub(&np_sub, neg_c, pos_b);
        
#if T_TEST_ALL_CASE == 1
        bi_new(&z,1);
        bi_sub(&pz_sub, pos_b, z);
        bi_sub(&nz_sub, neg_c, z);
        bi_sub(&zp_sub, z, pos_b);
        bi_sub(&zn_sub, z, neg_c);
        bi_sub(&zz_sub, z, z);
#endif
    }
    bi_delete(&pos_a);
    bi_delete(&pos_b);
    bi_delete(&neg_c);
    bi_delete(&neg_d);
    bi_delete(&pp_sub);
    bi_delete(&nn_sub);
    bi_delete(&pn_sub);
    bi_delete(&np_sub);

#if T_TEST_ALL_CASE == 1
    bi_delete(&z);
    bi_delete(&pz_sub);
    bi_delete(&zn_sub);
    bi_delete(&nz_sub);
    bi_delete(&zp_sub);
    bi_delete(&zz_sub);
#endif

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[sub] Execution time: %f seconds\n", cpu_time_used);
}


/**
 * @brief Runs a time test for bigint multiplication operation.
 *
 * This function measures the execution time of the bigint multiplication operation.
 * It is used to benchmark the performance of the multiplication function and
 * validate its efficiency.
 *
 * @return void
 */
void bignum_mul_time_test()
{
    clock_t start, end;
    double cpu_time_used;



    bigint *pos_a = NULL;
    bigint *pos_b = NULL;
    bigint *neg_c = NULL;
    bigint *neg_d = NULL;
    bigint *pp_mul = NULL;
    bigint *nn_mul = NULL;
    bigint *pn_mul = NULL;
    bigint *np_mul = NULL;

#if T_TEST_ALL_CASE == 1
    bigint *z = NULL;
    bigint *pz_mul = NULL;
    bigint *nz_mul = NULL;
    bigint *zp_mul = NULL;
    bigint *zn_mul = NULL;
    bigint *zz_mul = NULL;
#endif

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE);
#endif
        start = clock();
        bi_mul(&pp_mul, pos_a, pos_b);
        end = clock();
        bi_mul(&nn_mul, neg_c, neg_d);
        bi_mul(&pn_mul, pos_a, neg_d);
        bi_mul(&np_mul, neg_c, pos_b);
        
#if T_TEST_ALL_CASE == 1
        bi_new(&z,1);
        bi_mul(&pz_mul, pos_b, z);
        bi_mul(&nz_mul, neg_c, z);
        bi_mul(&zp_mul, z, pos_b);
        bi_mul(&zn_mul, z, neg_c);
        bi_mul(&zz_mul, z, z);
#endif
    }
    bi_delete(&pos_a);
    bi_delete(&pos_b);
    bi_delete(&neg_c);
    bi_delete(&neg_d);
    bi_delete(&pp_mul);
    bi_delete(&nn_mul);
    bi_delete(&pn_mul);
    bi_delete(&np_mul);

#if T_TEST_ALL_CASE == 1
    bi_delete(&z);
    bi_delete(&pz_mul);
    bi_delete(&zn_mul);
    bi_delete(&nz_mul);
    bi_delete(&zp_mul);
    bi_delete(&zz_mul);
#endif
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[mul] Execution time: %f seconds\n", cpu_time_used);
}

/**
 * @brief Runs a time test for bigint multiplication using Karatsuba algorithm.
 *
 * This function measures the execution time of the bigint multiplication 
 * using the Karatsuba algorithm. It is used to benchmark the performance 
 * of the Karatsuba multiplication approach for big numbers and validate 
 * its efficiency.
 *
 * @return void
 */
void bignum_mul_k_time_test()
{
    clock_t start, end;
    double cpu_time_used;



    bigint *pos_a = NULL;
    bigint *pos_b = NULL;
    bigint *neg_c = NULL;
    bigint *neg_d = NULL;
    bigint *pp_mul = NULL;
    bigint *nn_mul = NULL;
    bigint *pn_mul = NULL;
    bigint *np_mul = NULL;

#if T_TEST_ALL_CASE == 1
    bigint *z = NULL;
    bigint *pz_mul = NULL;
    bigint *nz_mul = NULL;
    bigint *zp_mul = NULL;
    bigint *zn_mul = NULL;
    bigint *zz_mul = NULL;
#endif

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE);
#endif
        start = clock();
        bi_mul_kara(&pp_mul, pos_a, pos_b);
        end = clock();
        bi_mul_kara(&nn_mul, neg_c, neg_d);
        bi_mul_kara(&pn_mul, pos_a, neg_d);
        bi_mul_kara(&np_mul, neg_c, pos_b);
        
#if T_TEST_ALL_CASE == 1
        bi_new(&z,1);
        bi_mul_kara(&pz_mul, pos_b, z);
        bi_mul_kara(&nz_mul, neg_c, z);
        bi_mul_kara(&zp_mul, z, pos_b);
        bi_mul_kara(&zn_mul, z, neg_c);
        bi_mul_kara(&zz_mul, z, z);
#endif
    }
    bi_delete(&pos_a);
    bi_delete(&pos_b);
    bi_delete(&neg_c);
    bi_delete(&neg_d);
    bi_delete(&pp_mul);
    bi_delete(&nn_mul);
    bi_delete(&pn_mul);
    bi_delete(&np_mul);

#if T_TEST_ALL_CASE == 1
    bi_delete(&z);
    bi_delete(&pz_mul);
    bi_delete(&zn_mul);
    bi_delete(&nz_mul);
    bi_delete(&zp_mul);
    bi_delete(&zz_mul);
#endif
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[mul_k] Execution time: %f seconds\n", cpu_time_used);
}


/**
 * @brief Runs a time test for bigint division operation.
 *
 * This function measures the execution time of the bigint division operation. 
 * It is used to benchmark the performance of the division function and 
 * validate its efficiency.
 *
 * @return void
 */
void bignum_div_time_test()
{
    clock_t start, end;
    double cpu_time_used;



    bigint *pos_a = NULL;
    bigint *pos_b = NULL;
    bigint *neg_c = NULL;
    bigint *neg_d = NULL;
    bigint *pp_quotient = NULL;
    bigint *pp_remainder = NULL;
    bigint *nn_quotient = NULL;
    bigint *nn_remainder = NULL;
    bigint *pn_quotient = NULL;
    bigint *pn_remainder = NULL;
    bigint *np_quotient = NULL;
    bigint *np_remainder = NULL;

#if T_TEST_ALL_CASE == 1
    bigint *z = NULL;
    bigint *zp_quotient = NULL;
    bigint *zp_remainder = NULL;
    bigint *zn_quotient = NULL;
    bigint *zn_remainder = NULL;
#endif

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE);
#endif
        start = clock();
        bi_word_division(&pp_quotient, &pp_remainder, pos_a, pos_b);
        end = clock();
        bi_word_division(&nn_quotient, &nn_remainder, neg_c, neg_d);
        bi_word_division(&pn_quotient, &pn_remainder, pos_a, neg_d);
        bi_word_division(&np_quotient, &np_remainder, neg_c, pos_b);
        
#if T_TEST_ALL_CASE == 1
        bi_new(&z,1);
        bi_word_division(&zp_quotient, &zp_remainder, z, pos_b);
        bi_word_division(&zn_quotient, &zn_remainder, z, neg_c);

#endif
    }
    bi_delete(&pos_a);
    bi_delete(&pos_b);
    bi_delete(&neg_c);
    bi_delete(&neg_d);
    bi_delete(&pp_quotient);
    bi_delete(&pp_remainder);
    bi_delete(&nn_quotient);
    bi_delete(&nn_remainder);
    bi_delete(&np_quotient);
    bi_delete(&np_remainder);
    bi_delete(&pn_quotient);
    bi_delete(&pn_remainder);

#if T_TEST_ALL_CASE == 1
    bi_delete(&z);
    bi_delete(&zp_quotient);
    bi_delete(&zp_remainder);
    bi_delete(&zn_quotient);
    bi_delete(&zn_remainder);
#endif

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[div] Execution time: %f seconds\n", cpu_time_used);
}

void bignum_squ_time_test()
{
    clock_t start, end;
    double cpu_time_used;



    bigint *pos_a = NULL;
    bigint *neg_b = NULL;
    bigint *p_squ = NULL;
    bigint *n_squ = NULL;

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_b, POSITIVE, T_TEST_DATA_WORD_SIZE);
#endif
        start = clock();
        bi_squ(&p_squ, pos_a);
        bi_squ(&n_squ, neg_b);
        end = clock();
    }

    bi_delete(&pos_a);
    bi_delete(&neg_b);
    bi_delete(&p_squ);
    bi_delete(&n_squ);


    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("[squ] Execution time: %f seconds\n", cpu_time_used);
}


void bignum_squ__vs_mul_time_test()
{
    clock_t start_squ, end_squ, start_mul, end_mul;
    double squ_cpu_time_used, mul_cpu_time_used;
    double sum_time_squ = 0;
    double sum_time_mul = 0;
    

    bigint *pos_a = NULL;
    bigint *neg_b = NULL;
    bigint *p_squ = NULL;
    bigint *n_squ = NULL;
    bigint *p_mul = NULL;
    bigint *n_mul = NULL;

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&neg_b, NEGATIVE, T_TEST_DATA_WORD_SIZE);
#endif
        

        start_mul = clock();
        bi_mul(&p_mul, pos_a, pos_a);
        end_mul = clock();
        mul_cpu_time_used = ((double)(end_mul - start_mul)) / CLOCKS_PER_SEC;
        sum_time_mul += mul_cpu_time_used;

        start_squ = clock();
        bi_squ(&p_squ, pos_a);
        end_squ = clock();
        squ_cpu_time_used = ((double)(end_squ - start_squ)) / CLOCKS_PER_SEC;
        sum_time_squ += squ_cpu_time_used;
    }
    bi_delete(&pos_a);
    bi_delete(&neg_b);
    bi_delete(&p_squ);
    bi_delete(&n_squ);
    bi_delete(&p_mul);
    bi_delete(&n_mul);

    squ_cpu_time_used = ((double)(sum_time_squ / TESTNUM));
    printf("[squ] Execution time: %f seconds\n", squ_cpu_time_used);

    mul_cpu_time_used = ((double)(sum_time_mul / TESTNUM));
    printf("[mul] Execution time: %f seconds\n", mul_cpu_time_used);
}

void bignum_squ_vs_squ_k_time_test()
{
    clock_t start, end;
    double squ_time, squ_k_time;
    double squ_sum = 0; double squ_k_sum = 0; 
    
    bigint *pos_a = NULL;
    bigint *p_squ = NULL;

    for (int testnum = 0; testnum < TESTNUM; testnum++)
    {
#if T_TEST_WORD_LEN_RANDOM == 1
        bi_get_random(&pos_a, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&pos_b, POSITIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_c, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
        bi_get_random(&neg_d, NEGATIVE, T_TEST_DATA_WORD_SIZE % 63 + 1);
#elif T_TEST_WORD_LEN_RANDOM == 0
        bi_get_random(&pos_a, POSITIVE, 6);
#endif
        start = clock();
        bi_squ(&p_squ, pos_a);
        end = clock();
        squ_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        squ_sum += squ_time;

        start = clock();
        bi_squ_kara(&p_squ, pos_a);
        end = clock();
        squ_k_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        squ_k_sum += squ_k_time;
    }

    bi_delete(&pos_a);
    bi_delete(&p_squ);

    printf("[squ] Execution time: %f seconds\n", squ_sum / TESTNUM);
    printf("[squ_k] Execution time: %f seconds\n", squ_k_sum / TESTNUM);
}

void bignum_time_all_test(){

    printf("======================|Time Measuring|======================\n");
    clock_t start, end;
    double add_time, sub_time, mul_time, div_time, mul_k_time, \
     squ_time, squ_k_time, l2r_time, r2l_time, bar_reduce_time, mas_time, word_div_time;
    
    double add_sum, sub_sum, mul_sum, div_sum, mul_k_sum, \
     squ_sum, squ_k_sum, l2r_sum, r2l_sum, bar_reduce_sum, mas_sum, word_div_sum;

    add_sum = 0; sub_sum = 0; mul_sum = 0; div_sum = 0; mul_k_sum = 0; squ_sum = 0;
    squ_k_sum = 0; l2r_sum = 0; r2l_sum = 0; bar_reduce_sum = 0; mas_sum = 0, word_div_sum = 0;

    bigint *src1 = NULL;
    bigint *src2 = NULL;
    bigint *result = NULL;
    for(int i = 0; i < TESTNUM; i++){

        bi_get_random(&src1, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bi_get_random(&src2, POSITIVE, T_TEST_DATA_WORD_SIZE);

        //add
        start = clock();
        bi_add(&result, src1, src2);
        end = clock();
        add_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        add_sum += add_time;
        
        //sub
        start = clock();
        bi_sub(&result, src1, src2);
        end = clock();
        sub_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        sub_sum += sub_time;

        //mul
        start = clock();
        bi_mul(&result, src1, src2);
        end = clock();
        mul_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        mul_sum += mul_time;

        //mul_k
        start = clock();
        bi_mul_kara(&result, src1, src2);
        end = clock();
        mul_k_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        mul_k_sum += mul_k_time;

        //binary div
        bigint *quo = NULL;
        bigint *remainer = NULL;
        start = clock();
        bi_binary_division(&quo, &remainer, src1, src2);
        end = clock();
        div_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        div_sum += div_time;
         
        //squ
        start = clock();
        bi_squ(&result, src1);
        end = clock();
        squ_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        squ_sum += squ_time;

        //squ_k
        start = clock();
        bi_squ_kara(&result, src1);
        end = clock();
        squ_k_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        squ_k_sum += squ_k_time;
        
        bigint *exp = NULL;
        bi_get_random(&exp, POSITIVE, T_TEST_DATA_WORD_SIZE);
        bigint *modulo = NULL;
        bi_get_random(&modulo, POSITIVE, T_TEST_DATA_WORD_SIZE);
        
        //l2r   
        start = clock();
        bi_mod_exp_l2r(&result, src1, exp, modulo);
        end = clock();
        l2r_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        l2r_sum += l2r_time;

        //r2l
        start = clock();
        bi_mod_exp_r2l(&result, src1, exp, modulo);
        end = clock();
        r2l_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        r2l_sum += r2l_time;

        //Multiple and Square
        start = clock();
        bi_mod_exp_MaS(&result, src1, exp, modulo);
        end = clock();
        mas_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        mas_sum += mas_time;
        
        bi_delete(&exp);
        bi_delete(&modulo);

        //Barett Reduce
        int n = 32;
        bigint *A = NULL;
        bi_get_random(&A, POSITIVE, 2*n);
        bigint *N = NULL;
        bi_get_random(&N, POSITIVE, n);
        bigint *T = NULL;
        bigint *r_temp = NULL;
        bigint *W_2n = NULL;
        
        bi_new(&W_2n,n*2+1);
        W_2n->a[n*2] = 1;
        W_2n->sign = POSITIVE;
        bi_word_division(&T, &r_temp, W_2n, N);

        bigint *redu_result = NULL;

        start = clock();
        bi_bar_redu(&redu_result, A, T, N);
        end = clock();
        bar_reduce_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        bar_reduce_sum += bar_reduce_time;

        //Word Division
        start = clock();
        bi_word_division(&quo, &remainer, src1, src2);
        end = clock();
        word_div_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        word_div_sum += word_div_time;
        bi_delete(&quo);
        bi_delete(&remainer);

        bi_delete(&A);
        bi_delete(&N);
        bi_delete(&T);
        bi_delete(&r_temp);
        bi_delete(&W_2n);
        bi_delete(&redu_result);

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&result);
    }
    if(T_TEST_AVERAGE == 1)
    {
        printf("[add] Execution time: %f seconds\n", add_sum / TESTNUM);
        printf("[sub] Execution time: %f seconds\n", sub_sum / TESTNUM);
        printf("[mul] Execution time: %f seconds\n", mul_sum / TESTNUM);
        printf("[mul_k] Execution time: %f seconds\n", mul_k_sum / TESTNUM);
        printf("[div_bin] Execution time: %f seconds\n", div_sum / TESTNUM);
        printf("[div_word] Execution time: %f seconds\n", word_div_sum / TESTNUM);   
        printf("[squ] Execution time: %f seconds\n", squ_sum / TESTNUM);
        printf("[squ_k] Execution time: %f seconds\n", squ_k_sum / TESTNUM);
        printf("[l2r] Execution time: %f seconds\n", l2r_sum / TESTNUM);
        printf("[r2l] Execution time: %f seconds\n", r2l_sum / TESTNUM);
        printf("[Mas] Execution time: %f seconds\n", mas_sum / TESTNUM);   
        printf("[Bar_reduce] Execution time: %f seconds\n", bar_reduce_sum / TESTNUM);
    }
    else{
        printf("[add] Execution time: %f seconds\n", add_sum );
        printf("[sub] Execution time: %f seconds\n", sub_sum );
        printf("[mul] Execution time: %f seconds\n", mul_sum );
        printf("[mul_k] Execution time: %f seconds\n", mul_k_sum );
        printf("[div_bin] Execution time: %f seconds\n", div_sum );
        printf("[div_word] Execution time: %f seconds\n", word_div_sum);
        printf("[squ] Execution time: %f seconds\n", squ_sum );
        printf("[squ_k] Execution time: %f seconds\n", squ_k_sum );
        printf("[l2r] Execution time: %f seconds\n", l2r_sum);
        printf("[r2l] Execution time: %f seconds\n", r2l_sum);
        printf("[Mas] Execution time: %f seconds\n", mas_sum);   
        printf("[Bar_reduce] Execution time: %f seconds\n", bar_reduce_sum); 
    }

}


/**
 * @brief Runs a specific addition test from a file for validation.
 *
 * This function reads test cases from the specified file and executes an addition test based on the provided test number. 
 * It is commonly used for validating the correctness of bigint addition operations.
 *
 * @param filename The name of the file containing test cases.
 * @param testnum The specific test case number to run from the file.
 * @return void
 */
void python_add_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        
        bigint *pp_add = NULL;
        bi_add(&pp_add, pos_a, pos_b);

        bigint *nn_add = NULL;
        bi_add(&nn_add, neg_c, neg_d);

        bigint *pn_add = NULL;
        bi_add(&pn_add, pos_a, neg_d);

        bigint *np_add = NULL;
        bi_add(&np_add, neg_c, pos_b);
        
        
        bigint *pz_add = NULL;
        bi_add(&pz_add, pos_b, z);

        bigint *nz_add = NULL;
        bi_add(&nz_add, neg_c, z);

        bigint *zp_add = NULL;
        bi_add(&zp_add, z, pos_b);

        bigint *zn_add = NULL;
        bi_add(&zn_add, z, neg_c);

        bigint *zz_add = NULL;
        bi_add(&zz_add, z, z);

        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_add = ");
        bi_fprint(file,pp_add);
        fprintf(file, "nn_add = ");
        bi_fprint(file,nn_add);
        fprintf(file, "np_add = ");
        bi_fprint(file,np_add);
        fprintf(file, "pn_add = ");
        bi_fprint(file,pn_add);

        fprintf(file, "zp_add = ");
        bi_fprint(file,zp_add);
        fprintf(file, "zn_add = ");
        bi_fprint(file,zn_add);
        fprintf(file, "nz_add = ");
        bi_fprint(file,nz_add);
        fprintf(file, "pz_add = ");
        bi_fprint(file,pz_add);
        fprintf(file, "zz_add = ");
        bi_fprint(file,zz_add);

        fprintf(file, "if (pos_a + pos_b != pp_add):\n \t print(f\"[pp_add]: {pos_a:#x} + {pos_b:#x} != {pp_add:#x}\\n\")\n");
        fprintf(file, "if (neg_c + neg_d != nn_add):\n \t print(f\"[nn_add]: {neg_c:#x} + {neg_d:#x} != {nn_add:#x}\\n\")\n");
        fprintf(file, "if (pos_a + neg_d != pn_add):\n \t print(f\"[pn_add]: {pos_a:#x} + {neg_d:#x} != {pn_add:#x}\\n\")\n");
        fprintf(file, "if (neg_c + pos_b != np_add):\n \t print(f\"[np_add]: {neg_c:#x} + {pos_b:#x} != {np_add:#x}\\n\")\n");

        fprintf(file, "if (pos_b + z != pz_add):\n \t print(f\"[pz_add]: {pos_b:#x} + {z:#x} != {pz_add:#x}\\n\")\n");
        fprintf(file, "if (neg_c + z != nz_add):\n \t print(f\"[nz_add]: {neg_c:#x} + {z:#x} != {nz_add:#x}\\n\")\n");
        fprintf(file, "if (z + pos_b != zp_add):\n \t print(f\"[zp_add]: {z:#x} + {pos_b:#x} != {zp_add:#x}\\n\")\n");
        fprintf(file, "if (z + neg_c != zn_add):\n \t print(f\"[zn_add]: {z:#x} + {neg_c:#x} != {zn_add:#x}\\n\")\n");
        fprintf(file, "if (z + z != zz_add):\n \t print(f\"[zz_add]: {z:#x} + {z:#x} != {zz_add:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_add);
        bi_delete(&nn_add);
        bi_delete(&pn_add);
        bi_delete(&np_add);

        bi_delete(&pz_add);
        bi_delete(&zn_add);
        bi_delete(&nz_add);
        bi_delete(&zp_add);
        bi_delete(&zz_add);
    }   
    fclose(file);
}


/**
 * @brief Runs a specific subtraction test from a file for validation.
 *
 * This function reads test cases from the specified file and executes a subtraction test based on the provided test number.
 * It is commonly used for validating the correctness of bigint subtraction operations.
 *
 * @param filename The name of the file containing test cases.
 * @param testnum The specific test case number to run from the file.
 * @return void
 */
void python_sub_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        bigint *pp_sub = NULL;
        bi_sub(&pp_sub, pos_a, pos_b);

        bigint *nn_sub = NULL;
        bi_sub(&nn_sub, neg_c, neg_d);

        bigint *pn_sub = NULL;
        bi_sub(&pn_sub, pos_a, neg_d);

        bigint *np_sub = NULL;
        bi_sub(&np_sub, neg_c, pos_b);
        
        bigint *pz_sub = NULL;
        bi_sub(&pz_sub, pos_b, z);

        bigint *nz_sub = NULL;
        bi_sub(&nz_sub, neg_c, z);

        bigint *zp_sub = NULL;
        bi_sub(&zp_sub, z, pos_b);

        bigint *zn_sub = NULL;
        bi_sub(&zn_sub, z, neg_c);

        bigint *zz_sub = NULL;
        bi_sub(&zz_sub, z, z);

        //
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_sub = ");
        bi_fprint(file,pp_sub);
        fprintf(file, "nn_sub = ");
        bi_fprint(file,nn_sub);
        fprintf(file, "np_sub = ");
        bi_fprint(file,np_sub);
        fprintf(file, "pn_sub = ");
        bi_fprint(file,pn_sub);

        fprintf(file, "zp_sub = ");
        bi_fprint(file,zp_sub);
        fprintf(file, "zn_sub = ");
        bi_fprint(file,zn_sub);
        fprintf(file, "nz_sub = ");
        bi_fprint(file,nz_sub);
        fprintf(file, "pz_sub = ");
        bi_fprint(file,pz_sub);
        fprintf(file, "zz_sub = ");
        bi_fprint(file,zz_sub);

        fprintf(file, "if (pos_a - pos_b != pp_sub):\n \t print(f\"[pp_sub]: {pos_a:#x} + {pos_b:#x} != {pp_sub:#x}\\n\")\n");
        fprintf(file, "if (neg_c - neg_d != nn_sub):\n \t print(f\"[nn_sub]: {neg_c:#x} + {neg_d:#x} != {nn_sub:#x}\\n\")\n");
        fprintf(file, "if (pos_a - neg_d != pn_sub):\n \t print(f\"[pn_sub]: {pos_a:#x} + {neg_d:#x} != {pn_sub:#x}\\n\")\n");
        fprintf(file, "if (neg_c - pos_b != np_sub):\n \t print(f\"[np_sub]: {neg_c:#x} + {pos_b:#x} != {np_sub:#x}\\n\")\n");

        fprintf(file, "if (pos_b - z != pz_sub):\n \t print(f\"[pz_sub]: {pos_b:#x} - {z:#x} != {pz_sub:#x}\\n\")\n");
        fprintf(file, "if (neg_c - z != nz_sub):\n \t print(f\"[nz_sub]: {neg_c:#x} - {z:#x} != {nz_sub:#x}\\n\")\n");
        fprintf(file, "if (z - pos_b != zp_sub):\n \t print(f\"[zp_sub]: {z:#x} - {pos_b:#x} != {zp_sub:#x}\\n\")\n");
        fprintf(file, "if (z - neg_c != zn_sub):\n \t print(f\"[zn_sub]: {z:#x} - {neg_c:#x} != {zn_sub:#x}\\n\")\n");
        fprintf(file, "if (z - z != zz_sub):\n \t print(f\"[zz_sub]: {z:#x} - {z:#x} != {zz_sub:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_sub);
        bi_delete(&nn_sub);
        bi_delete(&pn_sub);
        bi_delete(&np_sub);

        bi_delete(&pz_sub);
        bi_delete(&zn_sub);
        bi_delete(&nz_sub);
        bi_delete(&zp_sub);
        bi_delete(&zz_sub);
    }   
    fclose(file);
}


/**
 * @brief Runs a specific multiplication test from a file for validation.
 *
 * This function reads test cases from the specified file and executes a multiplication test based on the provided test number.
 * It is commonly used for validating the correctness of bigint multiplication operations.
 *
 * @param filename The name of the file containing test cases.
 * @param testnum The specific test case number to run from the file.
 * @return void
 */
void python_mul_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        bigint *pp_mul = NULL;
        bi_mul(&pp_mul, pos_a, pos_b);

        bigint *nn_mul = NULL;
        bi_mul(&nn_mul, neg_c, neg_d);

        bigint *pn_mul = NULL;
        bi_mul(&pn_mul, pos_a, neg_d);

        bigint *np_mul = NULL;
        bi_mul(&np_mul, neg_c, pos_b);
        
        bigint *pz_mul = NULL;
        bi_mul(&pz_mul, pos_b, z);

        bigint *nz_mul = NULL;
        bi_mul(&nz_mul, neg_c, z);

        bigint *zp_mul = NULL;
        bi_mul(&zp_mul, z, pos_b);

        bigint *zn_mul = NULL;
        bi_mul(&zn_mul, z, neg_c);

        bigint *zz_mul = NULL;
        bi_mul(&zz_mul, z, z);

        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_mul = ");
        bi_fprint(file,pp_mul);
        fprintf(file, "nn_mul = ");
        bi_fprint(file,nn_mul);
        fprintf(file, "np_mul = ");
        bi_fprint(file,np_mul);
        fprintf(file, "pn_mul = ");
        bi_fprint(file,pn_mul);

        fprintf(file, "zp_mul = ");
        bi_fprint(file,zp_mul);
        fprintf(file, "zn_mul = ");
        bi_fprint(file,zn_mul);
        fprintf(file, "nz_mul = ");
        bi_fprint(file,nz_mul);
        fprintf(file, "pz_mul = ");
        bi_fprint(file,pz_mul);
        fprintf(file, "zz_mul = ");
        bi_fprint(file,zz_mul);

        fprintf(file, "if (pos_a * pos_b != pp_mul):\n \t print(f\"[pp_mul]: {pos_a:#x} + {pos_b:#x} != {pp_mul:#x}\\n\")\n");
        fprintf(file, "if (neg_c * neg_d != nn_mul):\n \t print(f\"[nn_mul]: {neg_c:#x} + {neg_d:#x} != {nn_mul:#x}\\n\")\n");
        fprintf(file, "if (pos_a * neg_d != pn_mul):\n \t print(f\"[pn_mul]: {pos_a:#x} + {neg_d:#x} != {pn_mul:#x}\\n\")\n");
        fprintf(file, "if (neg_c * pos_b != np_mul):\n \t print(f\"[np_mul]: {neg_c:#x} + {pos_b:#x} != {np_mul:#x}\\n\")\n");

        fprintf(file, "if (pos_b * z != pz_mul):\n \t print(f\"[pz_mul]: {pos_b:#x} - {z:#x} != {pz_mul:#x}\\n\")\n");
        fprintf(file, "if (neg_c * z != nz_mul):\n \t print(f\"[nz_mul]: {neg_c:#x} - {z:#x} != {nz_mul:#x}\\n\")\n");
        fprintf(file, "if (z * pos_b != zp_mul):\n \t print(f\"[zp_mul]: {z:#x} - {pos_b:#x} != {zp_mul:#x}\\n\")\n");
        fprintf(file, "if (z * neg_c != zn_mul):\n \t print(f\"[zn_mul]: {z:#x} - {neg_c:#x} != {zn_mul:#x}\\n\")\n");
        fprintf(file, "if (z * z != zz_mul):\n \t print(f\"[zz_mul]: {z:#x} - {z:#x} != {zz_mul:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_mul);
        bi_delete(&nn_mul);
        bi_delete(&pn_mul);
        bi_delete(&np_mul);

        bi_delete(&pz_mul);
        bi_delete(&zn_mul);
        bi_delete(&nz_mul);
        bi_delete(&zp_mul);
        bi_delete(&zz_mul);
    }   
    fclose(file);
}


/**
 * @brief Runs a specific multiplication test from a file for validation.
 *
 * This function reads test cases from the specified file and executes a multiplication test based on the provided test number.
 * It is commonly used for validating the correctness of bigint multiplication operations.
 *
 * @param filename The name of the file containing test cases.
 * @param testnum The specific test case number to run from the file.
 * @return void
 */
void python_mul_k_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        bigint *pp_mul = NULL;
        bi_mul_kara(&pp_mul, pos_a, pos_b);

        bigint *nn_mul = NULL;
        bi_mul_kara(&nn_mul, neg_c, neg_d);

        bigint *pn_mul = NULL;
        bi_mul_kara(&pn_mul, pos_a, neg_d);

        bigint *np_mul = NULL;
        bi_mul_kara(&np_mul, neg_c, pos_b);
        
        bigint *pz_mul = NULL;
        bi_mul_kara(&pz_mul, pos_b, z);

        bigint *nz_mul = NULL;
        bi_mul_kara(&nz_mul, neg_c, z);

        bigint *zp_mul = NULL;
        bi_mul_kara(&zp_mul, z, pos_b);

        bigint *zn_mul = NULL;
        bi_mul_kara(&zn_mul, z, neg_c);

        bigint *zz_mul = NULL;
        bi_mul_kara(&zz_mul, z, z);

        //
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_mul = ");
        bi_fprint(file,pp_mul);
        fprintf(file, "nn_mul = ");
        bi_fprint(file,nn_mul);
        fprintf(file, "np_mul = ");
        bi_fprint(file,np_mul);
        fprintf(file, "pn_mul = ");
        bi_fprint(file,pn_mul);

        fprintf(file, "zp_mul = ");
        bi_fprint(file,zp_mul);
        fprintf(file, "zn_mul = ");
        bi_fprint(file,zn_mul);
        fprintf(file, "nz_mul = ");
        bi_fprint(file,nz_mul);
        fprintf(file, "pz_mul = ");
        bi_fprint(file,pz_mul);
        fprintf(file, "zz_mul = ");
        bi_fprint(file,zz_mul);

        fprintf(file, "if (pos_a * pos_b != pp_mul):\n \t print(f\"[pp_mul]: {pos_a:#x} * {pos_b:#x} != {pp_mul:#x}\\n\")\n");
        fprintf(file, "if (neg_c * neg_d != nn_mul):\n \t print(f\"[nn_mul]: {neg_c:#x} * {neg_d:#x} != {nn_mul:#x}\\n\")\n");
        fprintf(file, "if (pos_a * neg_d != pn_mul):\n \t print(f\"[pn_mul]: {pos_a:#x} * {neg_d:#x} != {pn_mul:#x}\\n\")\n");
        fprintf(file, "if (neg_c * pos_b != np_mul):\n \t print(f\"[np_mul]: {neg_c:#x} * {pos_b:#x} != {np_mul:#x}\\n\")\n");

        fprintf(file, "if (pos_b * z != pz_mul):\n \t print(f\"[pz_mul]: {pos_b:#x} * {z:#x} != {pz_mul:#x}\\n\")\n");
        fprintf(file, "if (neg_c * z != nz_mul):\n \t print(f\"[nz_mul]: {neg_c:#x} * {z:#x} != {nz_mul:#x}\\n\")\n");
        fprintf(file, "if (z * pos_b != zp_mul):\n \t print(f\"[zp_mul]: {z:#x} * {pos_b:#x} != {zp_mul:#x}\\n\")\n");
        fprintf(file, "if (z * neg_c != zn_mul):\n \t print(f\"[zn_mul]: {z:#x} * {neg_c:#x} != {zn_mul:#x}\\n\")\n");
        fprintf(file, "if (z * z != zz_mul):\n \t print(f\"[zz_mul]: {z:#x} * {z:#x} != {zz_mul:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_mul);
        bi_delete(&nn_mul);
        bi_delete(&pn_mul);
        bi_delete(&np_mul);

        bi_delete(&pz_mul);
        bi_delete(&zn_mul);
        bi_delete(&nz_mul);
        bi_delete(&zp_mul);
        bi_delete(&zz_mul);
    }   
    fclose(file);
}



/**
 * @brief Runs a specific division test from a file for validation.
 *
 * This function reads test cases from the specified file and executes a division test based on the provided test number.
 * It is primarily used for validating the correctness of bigint division operations, including both quotient and remainder.
 *
 * @param filename The name of the file containing the test cases for bigint division.
 * @param testnum The specific test case number to execute from the file.
 * @return void
 */
void python_bin_div_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        bigint *pp_quotient = NULL;
        bigint *pp_remainder = NULL;
        bi_binary_division(&pp_quotient, &pp_remainder, pos_a, pos_b);

        bigint *nn_quotient = NULL;
        bigint *nn_remainder = NULL;
        bi_binary_division(&nn_quotient, &nn_remainder, neg_c, neg_d);

        bigint *pn_quotient = NULL;
        bigint *pn_remainder = NULL;
        bi_binary_division(&pn_quotient, &pn_remainder, pos_a, neg_d);

        bigint *np_quotient = NULL;
        bigint *np_remainder = NULL;
        bi_binary_division(&np_quotient, &np_remainder, neg_c, pos_b);

        bigint *zp_quotient = NULL;
        bigint *zp_remainder = NULL;
        bi_binary_division(&zp_quotient, &zp_remainder, z, pos_b);

        bigint *zn_quotient = NULL;
        bigint *zn_remainder = NULL;
        bi_binary_division(&zn_quotient, &zn_remainder, z, neg_c);

        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_quotient = ");
        bi_fprint(file, pp_quotient);
        fprintf(file, "pp_remainder = ");
        bi_fprint(file, pp_remainder);
        fprintf(file, "nn_quotient = ");
        bi_fprint(file, nn_quotient);
        fprintf(file, "nn_remainder = ");
        bi_fprint(file, nn_remainder);
        fprintf(file, "np_quotient = ");
        bi_fprint(file, np_quotient);
        fprintf(file, "np_remainder = ");
        bi_fprint(file, np_remainder);
        fprintf(file, "pn_quotient = ");
        bi_fprint(file, pn_quotient);
        fprintf(file, "pn_remainder = ");
        bi_fprint(file, pn_remainder);

        fprintf(file, "zp_quotient = ");
        bi_fprint(file, zp_quotient);
        fprintf(file, "zp_remainder = ");
        bi_fprint(file, zp_remainder);
        fprintf(file, "zn_quotient = ");
        bi_fprint(file, zn_quotient);
        fprintf(file, "zn_remainder = ");
        bi_fprint(file, zn_remainder);


        fprintf(file, "if (pos_a // pos_b != pp_quotient):\n \t print(f\"[pp_quotient]: {pos_a:#x} // {pos_b:#x} != {pp_quotient:#x}\\n\")\n");
        fprintf(file, "if (pos_a %% pos_b != pp_remainder):\n \t print(f\"[pp_remainder]: {pos_a:#x} %% {pos_b:#x} != {pp_remainder:#x}\\n\")\n");
        fprintf(file, "if (neg_c // neg_d != nn_quotient):\n \t print(f\"[nn_quotient]: {neg_c:#x} // {neg_d:#x} != {nn_quotient:#x}\\n\")\n");
        fprintf(file, "if (neg_c %% neg_d != nn_remainder):\n \t print(f\"[nn_remainder]: {neg_c:#x} %% {neg_d:#x} != {nn_remainder:#x}\\n\")\n");
        fprintf(file, "if (neg_c // pos_b != np_quotient):\n \t print(f\"[np_quotient]: {neg_c:#x} // {pos_b:#x} != {np_quotient:#x}\\n\")\n");
        fprintf(file, "if (neg_c %% pos_b != np_remainder):\n \t print(f\"[np_remainder]: {neg_c:#x} %% {pos_b:#x} != {np_remainder:#x}\\n\")\n");
        fprintf(file, "if (pos_a // neg_d != pn_quotient):\n \t print(f\"[pn_quotient]: {pos_a:#x} // {neg_d:#x} != {pn_quotient:#x}\\n\")\n");
        fprintf(file, "if (pos_a %% neg_d != pn_remainder):\n \t print(f\"[pn_remainder]: {pos_a:#x} %% {neg_d:#x} != {pn_remainder:#x}\\n\")\n");


        fprintf(file, "if (z // pos_b != zp_quotient):\n \t print(f\"[zp_quotient]: {z:#x} // {pos_b:#x} != {zp_quotient:#x}\\n\")\n");
        fprintf(file, "if (z %% pos_b != zp_remainder):\n \t print(f\"[zp_remainder]: {z:#x} %% {pos_b:#x} != {zp_remainder:#x}\\n\")\n");
        fprintf(file, "if (z // neg_c != zn_quotient):\n \t print(f\"[zn_quotient]: {z:#x} // {neg_c:#x} != {zn_quotient:#x}\\n\")\n");
        fprintf(file, "if (z %% neg_c != zn_remainder):\n \t print(f\"[zn_remainder]: {z:#x} %% {neg_c:#x} != {zn_remainder:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_quotient);
        bi_delete(&pp_remainder);
        bi_delete(&nn_quotient);
        bi_delete(&nn_remainder);
        bi_delete(&np_quotient);
        bi_delete(&np_remainder);
        bi_delete(&pn_quotient);
        bi_delete(&pn_remainder);

        bi_delete(&zp_quotient);
        bi_delete(&zp_remainder);
        bi_delete(&zn_quotient);
        bi_delete(&zn_remainder);
    }   
    fclose(file);
}

/**
 * @brief Test function for word-level big integer division using Python-compatible data.
 * 
 * This function tests the word-level big integer division implementation by generating 
 * multiple random test cases and writing the results to a file. The output includes 
 * the test data and Python-compatible verification code for cross-checking results.
 * 
 * @param[in] filename The name of the file where the test data and Python verification code will be written.
 * @param[in] testnum The number of test cases to generate and execute.
 * 
 * @details
 * - Generates test cases for various combinations of big integers:
 *   - Positive/Positive, Negative/Negative, Positive/Negative, Negative/Positive, Zero/Positive, Zero/Negative.
 * - Performs the division using the `bi_word_division` function.
 * - Outputs:
 *   - Test data (`pos_a`, `pos_b`, `neg_c`, `neg_d`, `z`).
 *   - Results of division (quotient and remainder for each combination).
 *   - Python code snippets to verify the results using integer division and modulo operations.
 * - Handles dynamic memory allocation for all big integers used in the test cases.
 * - Ensures all allocated resources are cleaned up after each test case.
 * 
 * @return void. Prints an error message if the file cannot be opened.
 */

void python_word_div_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        bigint *pp_quotient = NULL;
        bigint *pp_remainder = NULL;
        bi_word_division(&pp_quotient, &pp_remainder, pos_a, pos_b);

        bigint *nn_quotient = NULL;
        bigint *nn_remainder = NULL;
        bi_word_division(&nn_quotient, &nn_remainder, neg_c, neg_d);

        bigint *pn_quotient = NULL;
        bigint *pn_remainder = NULL;
        bi_word_division(&pn_quotient, &pn_remainder, pos_a, neg_d);

        bigint *np_quotient = NULL;
        bigint *np_remainder = NULL;
        bi_word_division(&np_quotient, &np_remainder, neg_c, pos_b);

        bigint *zp_quotient = NULL;
        bigint *zp_remainder = NULL;
        bi_word_division(&zp_quotient, &zp_remainder, z, pos_b);

        bigint *zn_quotient = NULL;
        bigint *zn_remainder = NULL;
        bi_word_division(&zn_quotient, &zn_remainder, z, neg_c);

        
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_quotient = ");
        bi_fprint(file, pp_quotient);
        fprintf(file, "pp_remainder = ");
        bi_fprint(file, pp_remainder);
        fprintf(file, "nn_quotient = ");
        bi_fprint(file, nn_quotient);
        fprintf(file, "nn_remainder = ");
        bi_fprint(file, nn_remainder);
        fprintf(file, "np_quotient = ");
        bi_fprint(file, np_quotient);
        fprintf(file, "np_remainder = ");
        bi_fprint(file, np_remainder);
        fprintf(file, "pn_quotient = ");
        bi_fprint(file, pn_quotient);
        fprintf(file, "pn_remainder = ");
        bi_fprint(file, pn_remainder);

        fprintf(file, "zp_quotient = ");
        bi_fprint(file, zp_quotient);
        fprintf(file, "zp_remainder = ");
        bi_fprint(file, zp_remainder);
        fprintf(file, "zn_quotient = ");
        bi_fprint(file, zn_quotient);
        fprintf(file, "zn_remainder = ");
        bi_fprint(file, zn_remainder);


        fprintf(file, "if (pos_a // pos_b != pp_quotient):\n \t print(f\"[pp_quotient]: {pos_a:#x} // {pos_b:#x} != {pp_quotient:#x}\\n\")\n");
        fprintf(file, "if (pos_a %% pos_b != pp_remainder):\n \t print(f\"[pp_remainder]: {pos_a:#x} %% {pos_b:#x} != {pp_remainder:#x}\\n\")\n");
        fprintf(file, "if (neg_c // neg_d != nn_quotient):\n \t print(f\"[nn_quotient]: {neg_c:#x} // {neg_d:#x} != {nn_quotient:#x}\\n\")\n");
        fprintf(file, "if (neg_c %% neg_d != nn_remainder):\n \t print(f\"[nn_remainder]: {neg_c:#x} %% {neg_d:#x} != {nn_remainder:#x}\\n\")\n");
        fprintf(file, "if (neg_c // pos_b != np_quotient):\n \t print(f\"[np_quotient]: {neg_c:#x} // {pos_b:#x} != {np_quotient:#x}\\n\")\n");
        fprintf(file, "if (neg_c %% pos_b != np_remainder):\n \t print(f\"[np_remainder]: {neg_c:#x} %% {pos_b:#x} != {np_remainder:#x}\\n\")\n");
        fprintf(file, "if (pos_a // neg_d != pn_quotient):\n \t print(f\"[pn_quotient]: {pos_a:#x} // {neg_d:#x} != {pn_quotient:#x}\\n\")\n");
        fprintf(file, "if (pos_a %% neg_d != pn_remainder):\n \t print(f\"[pn_remainder]: {pos_a:#x} %% {neg_d:#x} != {pn_remainder:#x}\\n\")\n");


        fprintf(file, "if (z // pos_b != zp_quotient):\n \t print(f\"[zp_quotient]: {z:#x} // {pos_b:#x} != {zp_quotient:#x}\\n\")\n");
        fprintf(file, "if (z %% pos_b != zp_remainder):\n \t print(f\"[zp_remainder]: {z:#x} %% {pos_b:#x} != {zp_remainder:#x}\\n\")\n");
        fprintf(file, "if (z // neg_c != zn_quotient):\n \t print(f\"[zn_quotient]: {z:#x} // {neg_c:#x} != {zn_quotient:#x}\\n\")\n");
        fprintf(file, "if (z %% neg_c != zn_remainder):\n \t print(f\"[zn_remainder]: {z:#x} %% {neg_c:#x} != {zn_remainder:#x}\\n\")\n");


        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_quotient);
        bi_delete(&pp_remainder);
        bi_delete(&nn_quotient);
        bi_delete(&nn_remainder);
        bi_delete(&np_quotient);
        bi_delete(&np_remainder);
        bi_delete(&pn_quotient);
        bi_delete(&pn_remainder);

        bi_delete(&zp_quotient);
        bi_delete(&zp_remainder);
        bi_delete(&zn_quotient);
        bi_delete(&zn_remainder);
    }   
    fclose(file);
}

/**
 * @brief Test function for naive big integer division using Python-compatible data.
 * 
 * This function generates random test cases for `bi_naive_division` and writes the results,
 * along with Python-compatible verification code, to a specified file. The test covers
 * various input combinations to ensure correctness of the division operation.
 * 
 * @param[in] filename The name of the file where test data and Python verification code will be written.
 * 
 * @details
 * - Generates random test data for:
 *   - Two positive big integers (`pos_a`, `pos_b`).
 *   - Two negative big integers (`neg_c`, `neg_d`).
 *   - A zero big integer (`z`).
 * - Performs naive division using `bi_naive_division` for all combinations:
 *   - Positive/Positive, Negative/Negative, Positive/Negative, Negative/Positive, Zero/Positive, Zero/Negative.
 * - Outputs:
 *   - Test data (`pos_a`, `pos_b`, `neg_c`, `neg_d`, `z`).
 *   - Results of division (quotient and remainder for each combination).
 *   - Python code snippets for verification using integer division and modulo operations.
 * - Ensures all dynamically allocated memory for big integers is properly released after each test case.
 * - Provides an extensive test suite to validate the correctness of the naive division implementation.
 * 
 * @return void. Prints an error message if the file cannot be opened.
 */

void python_naive_div_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        bigint *pp_quotient = NULL;
        bigint *pp_remainder = NULL;
        bi_naive_division(&pp_quotient, &pp_remainder, pos_a, pos_b);

        bigint *nn_quotient = NULL;
        bigint *nn_remainder = NULL;
        bi_naive_division(&nn_quotient, &nn_remainder, neg_c, neg_d);

        bigint *pn_quotient = NULL;
        bigint *pn_remainder = NULL;
        bi_naive_division(&pn_quotient, &pn_remainder, pos_a, neg_d);

        bigint *np_quotient = NULL;
        bigint *np_remainder = NULL;
        bi_naive_division(&np_quotient, &np_remainder, neg_c, pos_b);

        bigint *zp_quotient = NULL;
        bigint *zp_remainder = NULL;
        bi_naive_division(&zp_quotient, &zp_remainder, z, pos_b);

        bigint *zn_quotient = NULL;
        bigint *zn_remainder = NULL;
        bi_naive_division(&zn_quotient, &zn_remainder, z, neg_c);

        
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_quotient = ");
        bi_fprint(file, pp_quotient);
        fprintf(file, "pp_remainder = ");
        bi_fprint(file, pp_remainder);
        fprintf(file, "nn_quotient = ");
        bi_fprint(file, nn_quotient);
        fprintf(file, "nn_remainder = ");
        bi_fprint(file, nn_remainder);
        fprintf(file, "np_quotient = ");
        bi_fprint(file, np_quotient);
        fprintf(file, "np_remainder = ");
        bi_fprint(file, np_remainder);
        fprintf(file, "pn_quotient = ");
        bi_fprint(file, pn_quotient);
        fprintf(file, "pn_remainder = ");
        bi_fprint(file, pn_remainder);

        fprintf(file, "zp_quotient = ");
        bi_fprint(file, zp_quotient);
        fprintf(file, "zp_remainder = ");
        bi_fprint(file, zp_remainder);
        fprintf(file, "zn_quotient = ");
        bi_fprint(file, zn_quotient);
        fprintf(file, "zn_remainder = ");
        bi_fprint(file, zn_remainder);


        fprintf(file, "if (pos_a // pos_b != pp_quotient):\n \t print(f\"[pp_quotient]: {pos_a:#x} // {pos_b:#x} != {pp_quotient:#x}\\n\")\n");
        fprintf(file, "if (pos_a %% pos_b != pp_remainder):\n \t print(f\"[pp_remainder]: {pos_a:#x} %% {pos_b:#x} != {pp_remainder:#x}\\n\")\n");
        fprintf(file, "if (neg_c // neg_d != nn_quotient):\n \t print(f\"[nn_quotient]: {neg_c:#x} // {neg_d:#x} != {nn_quotient:#x}\\n\")\n");
        fprintf(file, "if (neg_c %% neg_d != nn_remainder):\n \t print(f\"[nn_remainder]: {neg_c:#x} %% {neg_d:#x} != {nn_remainder:#x}\\n\")\n");
        fprintf(file, "if (neg_c // pos_b != np_quotient):\n \t print(f\"[np_quotient]: {neg_c:#x} // {pos_b:#x} != {np_quotient:#x}\\n\")\n");
        fprintf(file, "if (neg_c %% pos_b != np_remainder):\n \t print(f\"[np_remainder]: {neg_c:#x} %% {pos_b:#x} != {np_remainder:#x}\\n\")\n");
        fprintf(file, "if (pos_a // neg_d != pn_quotient):\n \t print(f\"[pn_quotient]: {pos_a:#x} // {neg_d:#x} != {pn_quotient:#x}\\n\")\n");
        fprintf(file, "if (pos_a %% neg_d != pn_remainder):\n \t print(f\"[pn_remainder]: {pos_a:#x} %% {neg_d:#x} != {pn_remainder:#x}\\n\")\n");


        fprintf(file, "if (z // pos_b != zp_quotient):\n \t print(f\"[zp_quotient]: {z:#x} // {pos_b:#x} != {zp_quotient:#x}\\n\")\n");
        fprintf(file, "if (z %% pos_b != zp_remainder):\n \t print(f\"[zp_remainder]: {z:#x} %% {pos_b:#x} != {zp_remainder:#x}\\n\")\n");
        fprintf(file, "if (z // neg_c != zn_quotient):\n \t print(f\"[zn_quotient]: {z:#x} // {neg_c:#x} != {zn_quotient:#x}\\n\")\n");
        fprintf(file, "if (z %% neg_c != zn_remainder):\n \t print(f\"[zn_remainder]: {z:#x} %% {neg_c:#x} != {zn_remainder:#x}\\n\")\n");


        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_quotient);
        bi_delete(&pp_remainder);
        bi_delete(&nn_quotient);
        bi_delete(&nn_remainder);
        bi_delete(&np_quotient);
        bi_delete(&np_remainder);
        bi_delete(&pn_quotient);
        bi_delete(&pn_remainder);

        bi_delete(&zp_quotient);
        bi_delete(&zp_remainder);
        bi_delete(&zn_quotient);
        bi_delete(&zn_remainder);
    }   
    fclose(file);
}


void python_squ_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_b = NULL;
        bi_get_random(&neg_b,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);

        bigint *p_squ = NULL;
        bi_squ(&p_squ, pos_a);

        bigint *n_squ = NULL;
        bi_squ(&n_squ, neg_b);
        
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "neg_b = ");
        bi_fprint(file,neg_b);

        fprintf(file, "p_squ = ");
        bi_fprint(file,p_squ);
        fprintf(file, "n_squ = ");
        bi_fprint(file,n_squ);

        fprintf(file, "if (pos_a * pos_a != p_squ):\n \t print(f\"[p_squ]: {pos_a:#x} ^ 2 != {p_squ:#x}\\n\")\n");
        fprintf(file, "if (neg_b * neg_b != n_squ):\n \t print(f\"[n_squ]: {neg_b:#x} ^ 2 != {n_squ:#x}\\n\")\n");
        bi_delete(&pos_a);
        bi_delete(&neg_b);
        bi_delete(&p_squ);
        bi_delete(&n_squ);
    }   
    fclose(file);
}


void python_rshift_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < TESTNUM; i++) {
        bigint *num = NULL;
        bi_get_random(&num, POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        
        int shift_bits = rand() % T_TEST_DATA_WORD_SIZE + 1;
        bigint *rshift_result = NULL;
        bi_assign(&rshift_result, num);
        bi_bit_rshift(rshift_result, shift_bits);
        
        fprintf(file, "# TEST %d\n", i + 1);
        fprintf(file, "num = ");
        bi_fprint(file, num);
        fprintf(file, "shift_bits = %d\n", shift_bits);
        fprintf(file, "rshift_result = ");
        bi_fprint(file, rshift_result);

        fprintf(file, "if (num >> %d != rshift_result):\n", shift_bits);
        fprintf(file, "\tprint(f\"[rshift_result]: {num:#x} >> %d != {rshift_result:#x}\\n\")\n", shift_bits);

        bi_delete(&num);
        bi_delete(&rshift_result);
    }

    fclose(file);
}

void python_lshift_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    srand(time(NULL)); 

    for (int i = 0; i < TESTNUM; i++) {
        bigint *num = NULL;
        bi_get_random(&num, POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        
        int shift_bits = rand() % T_TEST_DATA_WORD_SIZE + 1;
        bigint *lshift_result = NULL;
        bi_assign(&lshift_result, num);
        bi_bit_lshift(lshift_result, shift_bits);
        
        fprintf(file, "# TEST %d\n", i + 1);
        fprintf(file, "num = ");
        bi_fprint(file, num);
        fprintf(file, "shift_bits = %d\n", shift_bits);
        fprintf(file, "lshift_result = ");
        bi_fprint(file, lshift_result);

        fprintf(file, "if (num << %d != lshift_result):\n", shift_bits);
        fprintf(file, "\tprint(f\"[lshift_result]: {num:#x} << %d != {lshift_result:#x}\\n\")\n", shift_bits);

        bi_delete(&num);
        bi_delete(&lshift_result);
    }

    fclose(file);
}

void python_squ_k_test(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);
        bigint *neg_b = NULL;
        bi_get_random(&neg_b,NEGATIVE, rand() % T_TEST_DATA_WORD_SIZE + 1);

        bigint *p_squ = NULL;
        bi_squ_kara(&p_squ, pos_a);

        bigint *n_squ = NULL;
        bi_squ_kara(&n_squ, neg_b);
        
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "neg_b = ");
        bi_fprint(file,neg_b);

        fprintf(file, "p_squ = ");
        bi_fprint(file,p_squ);
        fprintf(file, "n_squ = ");
        bi_fprint(file,n_squ);

        fprintf(file, "if (pos_a * pos_a != p_squ):\n \t print(f\"[p_squ]: {pos_a:#x} ^ 2 != {p_squ:#x}\\n\")\n\n");
        fprintf(file, "if (neg_b * neg_b != n_squ):\n \t print(f\"[n_squ]: {neg_b:#x} ^ 2 != {n_squ:#x}\\n\")\n\n");
        bi_delete(&pos_a);
        bi_delete(&neg_b);
        bi_delete(&p_squ);
        bi_delete(&n_squ);
    }   
    fclose(file);
}


/**
 * @brief Test function for left-to-right modular exponentiation using Python data.
 * 
 * This function tests the left-to-right modular exponentiation implementation 
 * using test cases loaded from a Python-generated file.
 * 
 * @param[in] filename The name of the file containing test data.
 * @param[in] testnum The number of test cases to execute.
 * 
 * @return void
 */
void python_l2r_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM_modexp; i++) {
        bigint *base = NULL;
        bi_get_random(&base, POSITIVE, rand() % 63 + 1);
        bigint *exp = NULL;
        bi_get_random(&exp, POSITIVE, rand() % 5 + 1);
        bigint *mod = NULL;
        bi_get_random(&mod, POSITIVE, rand() % 31 + 1); 

        bigint *mod_exp_result = NULL;
        bi_mod_exp_l2r(&mod_exp_result, base, exp, mod);
        
        fprintf(file, "base = ");
        bi_fprint(file,base);
        fprintf(file, "exp = ");
        bi_fprint(file,exp);

        fprintf(file, "mod = ");
        bi_fprint(file,mod);
        fprintf(file, "mod_exp_result = ");
        bi_fprint(file,mod_exp_result);

        fprintf(file, "temp = pow(base, exp, mod)\n");
        fprintf(file, "if (mod_exp_result != temp):\n \t print(f\"[l2r]: {base:#x} ^ {exp:#x} mod {mod:#x} != {mod_exp_result:#x}\\n\")\n\n");

        bi_delete(&base);
        bi_delete(&exp);
        bi_delete(&mod);
        bi_delete(&mod_exp_result);
    }   
    fclose(file);
}



/**
 * @brief Test function for right-to-left modular exponentiation using Python data.
 * 
 * This function tests the right-to-left modular exponentiation implementation 
 * using test cases loaded from a Python-generated file.
 * 
 * @param[in] filename The name of the file containing test data.
 * @param[in] testnum The number of test cases to execute.
 * 
 * @return void
 */
void python_r2l_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM_modexp; i++) {
        bigint *base = NULL;
        bi_get_random(&base, POSITIVE, rand() % 63 + 1);
        bigint *exp = NULL;
        bi_get_random(&exp, POSITIVE, rand() % 5 + 1);
        bigint *mod = NULL;
        bi_get_random(&mod, POSITIVE, rand() % 31 + 1);

        bigint *mod_exp_result = NULL;
        bi_mod_exp_r2l(&mod_exp_result, base, exp, mod);
        
        fprintf(file, "base = ");
        bi_fprint(file,base);
        fprintf(file, "exp = ");
        bi_fprint(file,exp);

        fprintf(file, "mod = ");
        bi_fprint(file,mod);
        fprintf(file, "mod_exp_result = ");
        bi_fprint(file,mod_exp_result);

        fprintf(file, "temp = pow(base, exp, mod)\n");
        fprintf(file, "if (mod_exp_result != temp):\n \t print(f\"[l2r]: {base:#x} ^ {exp:#x} mod {mod:#x} != {mod_exp_result:#x}\\n\")\n\n");

        bi_delete(&base);
        bi_delete(&exp);
        bi_delete(&mod);
        bi_delete(&mod_exp_result);
    }   
    fclose(file);
}


/**
 * @brief Test function for multiply and square modular exponentiation using Python data.
 * 
 * This function tests the multiply and square modular exponentiation implementation 
 * using test cases loaded from a Python-generated file.
 * 
 * @param[in] filename The name of the file containing test data.
 * @param[in] testnum The number of test cases to execute.
 * 
 * @return void
 */
void python_MaS_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM_modexp; i++) {
        bigint *base = NULL;
        bi_get_random(&base, POSITIVE, rand() % 63 + 1);
        bigint *exp = NULL;
        bi_get_random(&exp, POSITIVE, rand() % 5 + 1);
        bigint *mod = NULL;
        bi_get_random(&mod, POSITIVE, rand() % 31 + 1);

        bigint *mod_exp_result = NULL;
        bi_mod_exp_MaS(&mod_exp_result, base, exp, mod);
        
        fprintf(file, "base = ");
        bi_fprint(file,base);
        fprintf(file, "exp = ");
        bi_fprint(file,exp);

        fprintf(file, "mod = ");
        bi_fprint(file,mod);
        fprintf(file, "mod_exp_result = ");
        bi_fprint(file,mod_exp_result);

        fprintf(file, "temp = pow(base, exp, mod)\n");
        fprintf(file, "if (mod_exp_result != temp):\n \t print(f\"[MaS]: {base:#x} ^ {exp:#x} mod {mod:#x} != {mod_exp_result:#x}\\n\")\n\n");

        bi_delete(&base);
        bi_delete(&exp);
        bi_delete(&mod_exp_result);
    }   
    fclose(file);
}


/**
 * @brief Test function for Fast Reduction using Barrett Reduction using Python data.
 * 
 * This function tests the Fast Reduction using Barrett Reduction implementation 
 * using test cases loaded from a Python-generated file.
 * 
 * @param[in] filename The name of the file containing test data.
 * @param[in] testnum The number of test cases to execute.
 * 
 * @return void
 */
void python_bar_redu_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("FILE OPEN ERROR");
        return;
    }

    for (int i = 0; i < TESTNUM; i++) {
        int n = rand() % 31 + 1;

        bigint *A = NULL;
        bi_get_random(&A, POSITIVE, 2*n);
        bigint *N = NULL;
        bi_get_random(&N, POSITIVE, n);
        bigint *T = NULL;
        bigint *r_temp = NULL;
        bigint *W_2n = NULL;
        
        bi_new(&W_2n,n*2+1);
        W_2n->a[n*2] = 1;
        W_2n->sign = POSITIVE;
        bi_word_division(&T, &r_temp, W_2n, N);

        bigint *redu_result = NULL;
        bi_bar_redu(&redu_result, A, T, N);
        
        fprintf(file, "A = ");
        bi_fprint(file,A);
        fprintf(file, "T = ");
        bi_fprint(file,T);

        fprintf(file, "N = ");
        bi_fprint(file,N);
        fprintf(file, "redu_result = ");
        bi_fprint(file,redu_result);

        fprintf(file, "temp = A %% N\n");
        fprintf(file, "if (redu_result != temp):\n \t print(f\"[bar]: {A:#x} mod {N:#x} != {redu_result:#x}\\n\")\n\n");

        bi_delete(&A);
        bi_delete(&N);
        bi_delete(&r_temp);
        bi_delete(&T);
        bi_delete(&W_2n);
        bi_delete(&redu_result);
    }   
    fclose(file);
}



void python_rsa_test(const char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    fprintf(file, "from sympy import isprime\n");
    fprintf(file, "from sympy import gcd\n\n");
    for (int i = 0; i < TESTNUM; i++) {
        bigint* n = NULL;
        bigint* e = NULL;
        bigint* p = NULL;
        bigint* q = NULL;
        bigint* d = NULL;
        bigint* msg = NULL;
        bigint* c = NULL;
        bigint* msg_buf = NULL;
        bigint* zero = NULL;
        int bit_len = T_TEST_DATA_WORD_SIZE * SIZEOFWORD / 2;
        bi_new(&zero, 1);

        rsa_key_generation(&n, &e, &p, &q, &d, bit_len);
        bi_get_random_within_range(&msg, zero, n);
        rsa_encryption(&c, msg, e, n);
        rsa_decryption(&msg_buf, c, d, n);
        
        fprintf(file, "p = ");
        bi_fprint(file,p);
        fprintf(file, "q= ");
        bi_fprint(file,q);
        fprintf(file, "n = ");
        bi_fprint(file,n);
        fprintf(file, "e = ");
        bi_fprint(file,e);
        fprintf(file, "d = ");
        bi_fprint(file,d);
        fprintf(file, "msg = ");
        bi_fprint(file,msg);
        fprintf(file, "c = ");
        bi_fprint(file,c);
        fprintf(file, "msg_buf = ");
        bi_fprint(file,msg_buf);
        fprintf(file, "bit_len = %d\n", bit_len);
        fprintf(file, "p_bit_length = p.bit_length()\n");
        fprintf(file, "q_bit_length = q.bit_length()\n");   
        fprintf(file, "phi_n = (p - 1) * (q - 1)\n");

        fprintf(file, "if (p_bit_length != bit_len / 2):\n\t print(\"p bit_length wrong\")\n");
        fprintf(file, "if (q_bit_length != bit_len / 2):\n\t print(\"q bit_length wrong\")\n");
        fprintf(file, "if (not isprime(p)):\n \t print(f\"[p]: {p:#x} is not prime\")\n");
        fprintf(file, "if (not isprime(q)):\n \t print(f\"[q]: {q:#x} is not prime\")\n");
        fprintf(file, "if (gcd(e, phi_n) != 1):\n \t print(f\"[gcd(e, phi_n)] : gcd({e:#x}, {phi_n:#x})) != 1)\")\n");
        fprintf(file, "if (((e * d) %% phi_n) != 1):\n \t print(f\"[e] : ({e:#x} x {d:#x} mod {phi_n:#x}) != 1)\")\n");
        fprintf(file, "if (msg != msg_buf):\n \t print(f\"[rsa] : (msg != msg_buf)\")\n");

        bi_delete(&p);
        bi_delete(&e);
        bi_delete(&p);
        bi_delete(&q);
        bi_delete(&d);
        bi_delete(&msg);
        bi_delete(&c);
        bi_delete(&msg_buf);
        bi_delete(&zero);
    }   
    fclose(file);
}
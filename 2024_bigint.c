/*
    2024.10.22
*/
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

/**
 * @brief Tests the bi_new, bi_delete, and bi_print functions.
 *
 * This function demonstrates the creation, deletion, and printing of 
 * big integer (bigint) objects using the bi_new and bi_delete 
 * functions. It also tests the array_copy function for copying 
 * values between two bigint instances.
 *
 * The function initializes two bigint pointers, allocates memory for 
 * them, and sets their values to predefined negative integers. 
 * It then copies the values from one bigint to another and prints 
 * their representations in both binary and hexadecimal formats.
 *
 * If any of the bigint allocations fail, it prints an error message. 
 * Finally, the function attempts to delete the allocated big integer 
 * objects and checks for successful deallocation.
 *
 * @note Ensure that the bigint library is properly initialized before 
 *       calling this function. The function also uses an array_copy 
 *       utility to copy data between big integer arrays.
 *
 * @return void
 */
void bi_test1()
{
    printf("bi_new, bi_delete, bi_print test\n");
    bigint* test1 = NULL;
    bigint* test2 = NULL;
    bigint* test3 = NULL;
    bigint* test4 = NULL;
    int error_code = 0;

    error_code = bi_new(&test1, 3);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }

    error_code = bi_new(&test2, 3);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }

    error_code = bi_new(&test3, 3);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }

    error_code = bi_new(&test4, 3);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }

    printf("[Bigint value]\n");
    test1->sign = POSITIVE;
    test1->a[0] = 0xffffffff;
    test1->a[1] = 0xcccccccc;
    test1->a[2] = 0xaaaaaaaa;

    test2->sign = NEGATIVE;
    test2->a[0] = 0xdddddddd;
    test2->a[1] = 0xeeeeeeee;
    test2->a[2] = 0xffffffff;

    printf("[Positive]\n");
    bi_print(test1, 2);
    bi_print(test1, 16);

    printf("\n[Negative]\n");
    bi_print(test2, 2);
    bi_print(test2, 16);
    error_code = bi_delete(&test1);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
    error_code = bi_delete(&test2);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
    error_code = bi_delete(&test3);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
    error_code = bi_delete(&test4);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
}

/**
 * @brief Tests the bi_set_from_string and bi_set_from_array functions.
 *
 * This function demonstrates the functionality of converting 
 * strings in different number bases (binary, octal, hexadecimal) 
 * into big integer (bigint) objects using the bi_set_from_string 
 * function. It also tests the bi_set_from_array function to 
 * initialize a bigint from an array of words.
 *
 * The function initializes multiple bigint pointers, generates a 
 * random array of words, and sets the values of the big integer 
 * objects from the provided string representations of numbers in 
 * binary, octal, and hexadecimal formats. It prints the results 
 * to the console to verify successful conversion.
 *
 * @note Ensure that the bigint library is properly initialized 
 *       before calling this function. The array used in 
 *       bi_set_from_array is generated randomly for testing.
 *
 * @return void
 */
void bi_test2()
{
    printf("[bi_set_from_string, bi_set_from_array function test]\n");

    bigint* test1 = NULL;
    bigint* test2 = NULL;
    bigint* test3 = NULL;
    bigint* test4 = NULL;

    int error_code = 0;

    word array[16] = {0, };
    array_init(array, 16);
    array_rand(array, 16);

    printf("Test: bi_set_from_string\n");
    char binstr[] = "11111111111010101011110011101101";
    printf("string(binary): %s\n", binstr);
    printf("bi_set_from_string(bin)\n=>");
    bi_set_from_string(&test1, binstr, 2);
    bi_print(test1, 2);
    printf("=>");
    bi_print(test1, 16);

    char hexstr[] = "ab542548c1123412374109238df";
    printf("\nstring(hex): %s\n", hexstr);
    printf("bi_set_from_string(hex) test\n=>");
    bi_set_from_string(&test2, hexstr, 16);
    bi_print(test2, 2);
    printf("=>");
    bi_print(test2, 16);

    printf("\ntest bi_set_from_arrray(hex)\n");
    printf("array:\n0x");
    for(int index=15;index>=0;index--)
    {
        printf("%08x", array[index]);
    }
    printf("\n");
    bi_set_from_array(&test3, POSITIVE, 16, array);
    bi_print(test3, 16);
    printf("\n");
    error_code = bi_delete(&test1);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
    error_code = bi_delete(&test2);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
    error_code = bi_delete(&test3);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
    error_code = bi_delete(&test4);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
}

/**
 * @brief Tests the bi_get_random function.
 *
 * This function demonstrates the usage of the bi_get_random function 
 * by generating a random positive bigint and printing it in hexadecimal format.
 *
 * It initializes an array of `word` type with zeros and then calls 
 * `bi_get_random` to populate the `dst` pointer with a random bigint 
 * of specified length. The generated bigint is then printed to the 
 * console in base 16.
 *
 * @note Ensure that the bigint library is properly initialized before 
 *       calling this function.
 *
 * @return void
 */
void bi_test3()
{
    printf("bi_get_random test\n");

    bigint* dst = NULL;
    bi_get_random(&dst, POSITIVE, 4);

    printf("bi(hex): ");
    bi_print(dst, 16);

    int error_code = bi_delete(&dst);
    if(error_code == FAILED)
    {
        fprintf(stderr, "failed\n");
    }
}


/**
 * @brief Main function of the program.
 *
 * This function initializes the program by setting up a leak check
 * function to be called at program exit. It then calls the
 * `bigint_test2` function to perform specific tests related to the
 * bigint library.
 *
 * @return Returns 0 upon successful completion of the program.
 *
 * @note This function will call `check_leaks` to check for memory
 *       leaks when the program exits.
 */
void compare_test(){
    bigint *x = NULL;
    bigint *y = NULL;
    bigint *z = NULL;
    bigint *k = NULL;
    int result;
    bi_get_random(&x, POSITIVE, 5);
    bi_get_random(&y, POSITIVE, 5);
    bi_get_random(&z, NEGATIVE, 5);
    bi_get_random(&k, NEGATIVE, 5);
    bi_print(x,16);
    bi_print(y,16);
    bi_print(z,16);
    bi_print(k,16);
    //1
    result = bi_compare(x,z);
    printf("%d\n",result);
    //-1
    result = bi_compare(z,x);
    printf("%d\n",result);
    result = bi_compare(x,y);
    printf("%d\n",result);
    result = bi_compare(y,x);
    printf("%d\n",result);
    result = bi_compare(z,k);
    printf("%d\n",result);
    result = bi_compare(k,z);
    printf("%d\n",result);
    result = bi_compare(x,x);
    printf("%d\n",result);

    bi_delete(&x);
    bi_delete(&y);
    bi_delete(&z);
    bi_delete(&k);
}

void sub_test()
{
    bigint* x1 = NULL;
    bigint* x2 = NULL;
    bigint* y = NULL;
    
    msg error_msg = 0;

    error_msg = bi_get_random(&x1, POSITIVE, 4);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "sub test failed\n");
    }
    error_msg = bi_get_random(&x2, POSITIVE, 4);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "sub test failed\n");
    }
    bi_print(x1, 16);
    bi_print(x2, 16);

    error_msg = bi_sub(&y, x1, x2);
    bi_print(y, 16);

    bi_delete(&x1);
    bi_delete(&x2);
    bi_delete(&y);
}
void fillzero_test(){
    bigint* x1 = NULL;
    bigint* x2 = NULL;
    msg error_msg = 0;

    error_msg = bi_get_random(&x1, POSITIVE, 4);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "test failed\n");
    }
    error_msg = bi_get_random(&x2, POSITIVE, 4);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "test failed\n");
    }

    bi_fillzero(x1, 6, 1);
    bi_print(x1, 16);
    bi_fillzero(x2, 6, -1);
    bi_print(x2, 16);

    bi_delete(&x1);
    bi_delete(&x2);
}

void bi_single_mul_test()
{
    int error_msg = 0;
    
    word a = 0xac343874;
    word b = 0x9d8de389;
    bigint* dst = NULL;

    error_msg = bi_smul(&dst, a, b);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_single_mul_test_error\n");
    }

    bi_print(dst, 16);
    error_msg = bi_delete(&dst);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_single_mul_test_error\n");
    }
}

void bi_mulc_test()
{
    int error_msg = 0;
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    bi_get_random(&src1, POSITIVE, 8);
    bi_get_random(&src2, POSITIVE, 8);

    error_msg = bi_mulc(&dst, src1, src2);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_mulc_test_error\n");
    }

    bi_print(src1, 16);
    bi_print(src2, 16);
    bi_print(dst, 16);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}

void bi_mul_test()
{
    int error_msg = 0;
    
    bigint* test_1 = NULL;
    bigint* test_2 = NULL;
    bigint* dst = NULL;

    bi_get_random(&test_1, POSITIVE, 15);
    bi_get_random(&test_2, POSITIVE, 8);

    bi_print(test_1, 16);
    bi_print(test_2, 16);

    error_msg = bi_mul(&dst, test_1, test_2);

    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_mul_test_error\n");
    }

    bi_print(dst, 16);
    bi_delete(&test_1);
    bi_delete(&test_2);
    error_msg = bi_delete(&dst);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_mul_test_error\n");
    }
}

void bi_connect_test(){
    int error_msg = 0;
    
    bigint* test_1 = NULL;
    bigint* test_2 = NULL;
    bigint* dst = NULL;

    bi_get_random(&test_1, POSITIVE, 2);
    bi_get_random(&test_2, POSITIVE, 2);

    bi_print(test_1, 16);
    bi_print(test_2, 16);

    error_msg = bi_connect(&dst, test_1, test_2);
    bi_delete(&test_1);
    bi_delete(&test_2);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_single_mul_test_error\n");
    }

    bi_print(dst, 16);
    error_msg = bi_delete(&dst);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_single_mul_test_error\n");
    }
}


void bi_bits_shift_test()
{
    int error_msg = FAILED;

    bigint* dst1 = NULL;
    bigint* dst2 = NULL;

    bi_get_random(&dst1, POSITIVE, 4);

    bi_print(dst1, 2);

    error_msg = bi_bit_rshift(dst1, 127);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_shift_test\n");
    }
    bi_print(dst1, 2);

    bi_delete(&dst1);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_shift_test\n");
    }

    bi_get_random(&dst2, POSITIVE, 2);

    bi_print(dst2, 2);

    error_msg = bi_bit_lshift(dst2, 31);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_shift_test\n");
    }
    bi_print(dst2, 2);

    bi_delete(&dst2);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_shift_test\n");
    }
}


void bi_binary_division_test()
{
    int error_msg = FAILED;

    bigint* src_1 = NULL;
    bigint* src_2 = NULL;
    bigint* quotient = NULL;
    bigint* remainder = NULL;

    bi_get_random(&src_1, POSITIVE, 2);
    bi_get_random(&src_2, POSITIVE, 1);

    bi_print(src_1, 16);
    bi_print(src_2, 16);

    error_msg = bi_binary_long_division(&quotient, &remainder, src_1, src_2);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_binary_division_test\n");
    }

    bi_print(quotient, 16);
    bi_print(remainder, 16);
    
    bi_delete(&src_1);
    bi_delete(&src_2);
    bi_delete(&quotient);
    bi_delete(&remainder);
}

void bi_compare_test()
{
    bigint* src_1 = NULL;
    bigint* src_2 = NULL;

    bi_new(&src_1, 1);
    bi_get_random(&src_2, NEGATIVE, 2);

    printf("%d\n", bi_compare(src_1, src_2));

    bi_delete(&src_1);
    bi_delete(&src_2);
}

void bi_division_test()
{
    int error_msg = FAILED;

    bigint* src_1 = NULL;
    bigint* src_2 = NULL;
    bigint* quotient = NULL;
    bigint* remainder = NULL;

    bi_get_random(&src_1, NEGATIVE, rand() % 4 + 1);
    bi_get_random(&src_2, NEGATIVE, rand() % 4 + 1);

    printf("a = ");
    bi_print(src_1, 16);
    printf("b = ");
    bi_print(src_2, 16);

    error_msg = bi_division(&quotient, &remainder, src_1, src_2);
    if(error_msg == FAILED)
    {
        fprintf(stderr, "bi_binary_division_test\n");
    }

    printf("q = ");
    bi_print(quotient, 16);
    printf("r = ");
    bi_print(remainder, 16);
    
    bi_delete(&src_1);
    bi_delete(&src_2);
    bi_delete(&quotient);
    bi_delete(&remainder);
}

int main()
{   
    //atexit(check_leaks);
    //bi_test1();
    //bi_test2();
    //bi_test3();
    //compare_test();
    //sub_test();

    srand(time(NULL));

    //sage_add_test("add_test.py", 100000);
    //sage_sub_test("sub_test.py", 100000);
    //sage_mul_test("mul_test.py", 100000);
    sage_mul_k_test("mul_k_test.py", 10000);
    //sage_div_test("div_test.py", 10000);
    //bi_single_mul_test();
    // bi_mulc_test();
    //bi_mul_test();
    //fillzero_test();
    //bi_binary_division_test();
    //bi_binary_division_test2();
    //bi_compare_test();
    //bi_division_test();
    return 0;
}
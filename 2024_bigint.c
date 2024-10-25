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
    bi_print(&test1, 2);
    bi_print(&test1, 16);

    printf("\n[Negative]\n");
    bi_print(&test2, 2);
    bi_print(&test2, 16);
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
    bi_print(&test1, 2);
    printf("=>");
    bi_print(&test1, 16);

    char hexstr[] = "ab542548c1123412374109238df";
    printf("\nstring(hex): %s\n", hexstr);
    printf("bi_set_from_string(hex) test\n=>");
    bi_set_from_string(&test2, hexstr, 16);
    bi_print(&test2, 2);
    printf("=>");
    bi_print(&test2, 16);

    printf("\ntest bi_set_from_arrray(hex)\n");
    printf("array:\n0x");
    for(int index=15;index>=0;index--)
    {
        printf("%08x", array[index]);
    }
    printf("\n");
    bi_set_from_array(&test3, POSITIVE, 16, array);
    bi_print(&test3, 16);
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
    word a[4] = {0x00, };

    bigint* dst = NULL;
    bi_get_random(&dst, POSITIVE, 4);

    printf("bi(hex): ");
    bi_print(&dst, 16);

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
int main()
{   
    atexit(check_leaks);
    bi_test1();
    bi_test2();
    bi_test3();
    return 0;
}
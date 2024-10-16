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

// array_rand, bi_get_random test
void bigint_test1()
{
    printf("bi_get_random test\n");
    word a[4] = {0x00, };

    bigint* dst = NULL;
    bi_get_random(&dst, POSITIVE, 4);

    bi_print(&dst, 16);
}

// bi_new, bi_delete, bi_print test function
void bigint_test2()
{
    printf("bi_new, bi_delete, bi_print test\n");
    bigint* test = NULL;
    bigint* test1 = NULL;
    int error_code = 0;

    int result1 = bi_new(&test, 3);
    int result2 = bi_new(&test1, 3);
    
    if((result1 == FAILED) | (result2 == FAILED))
    {
        printf("failed\n");
    }

    test->sign = NEGATIVE;
    test->a[0] = 0xffffffff;
    test->a[1] = 0xcccccccc;
    test->a[2] = 0xaaaaaaaa;

    test1->sign = NEGATIVE;
    test1->a[0] = 0xdddddddd;
    test1->a[1] = 0xeeeeeeee;
    test1->a[2] = 0xffffffff;

    array_copy(test->a, test1->a, 3);

    bi_print(&test1, 16);
    bi_print(&test, 2);
    bi_print(&test, 16);

    error_code = bi_delete(&test);
    printf("%p", test);
    if(error_code == FAILED)
    {
        printf("failed\n");
    }
    bi_delete(&test);
    bi_delete(&test1);
}

void bigint_test3()
{
    printf("bi_set_from_string, bi_set_from_array function test\n");
    bigint* test1 = NULL;
    bigint* test2 = NULL;
    bigint* test3 = NULL;
    bigint* test4 = NULL;
    word array[16] = {0, };
    array_init(array, 16);
    array_rand(array, 16);
    char binstr[] = "0b11111111111010101011110011101101";
    printf("bi_set_from_string(bin)\n");
    bi_set_from_string(&test1, binstr, 2);

    char octstr[] = "075321056745";
    printf("bi_set_from_string(oct)\n");
    bi_set_from_string(&test2, octstr, 8);

    char hexstr[] = "0xab542548c1123412374109238df";
    printf("bi_set_from_string(hex)\n");
    bi_set_from_string(&test3, hexstr, 16);

    printf("bi_set_from_arrray(hex)\n");
    bi_set_from_array(&test4, POSITIVE, 16, array);
}

int main()
{
    atexit(check_leaks);
    bigint_test2();
    return 0;
}
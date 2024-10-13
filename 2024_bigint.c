/*
    2024.10.22
*/
#include <stdio.h>
#include "bigintfun.h"
#include "dtype.h"
#include "errormsg.h"
#include "params.h"

// bi_new, bi_delete, bi_print test function
void bigint_test1()
{
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
    // bi_print(&test, 2);
    // bi_print(&test, 16);

    // error_code = bi_delete(&test);
    // printf("%p", test);
    // if(error_code == FAILED)
    // {
    //     printf("failed\n");
    // }
}

// bi_refine, bi_assign test function
void bigint_test2()
{

}

int main()
{
    bigint_test1();
    
    return 0;
}
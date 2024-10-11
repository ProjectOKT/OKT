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
    int error_code = 0;

    error_code = bi_new(&test, 3);

    test->sign = NEGATIVE;
    test->a[0] = 0xffffffff;
    test->a[1] = 0xcccccccc;
    test->a[2] = 0xaaaaaaaa;
    if(error_code == FAILED)
    {
        printf("failed\n");
    }

    bi_print(&test, 2);
    bi_print(&test, 16);

    error_code = bi_delete(&test);
    printf("%p", test);
    if(error_code == FAILED)
    {
        printf("failed\n");
    }
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
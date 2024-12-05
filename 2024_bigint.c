#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "verify.h"
#include "operation.h"
#include "test.h"

int main()
{   
    atexit(check_leaks);
    
    srand(time(NULL));

    bignum_time_all_test();

    /*********************************************
     * generate python file and run test
    **********************************************/

    // python_lshift_test("lshift_test.py", 1000);
    // python_rshift_test("rshift_test.py", 1000);
    // python_add_test("add_test.py", 1000);
    // python_sub_test("sub_test.py", 1000);
    // python_mul_test("mul_test.py", 1000);
    // python_mul_k_test("mul_k_test.py", 1000);
    // python_div_test("div_test.py", 1000);
    // python_squ_test("squ_test.py", 1000);
    // python_squ_k_test("squ_k_test.py", 1000);
    // python_l2r_test("l2r_test.py", 100);
    // python_r2l_test("r2l_test.py", 100);
    // python_MaS_test("MaS_test.py", 100);
    // python_bar_redu_test("bar_redu_test.py", 1000);
    return 0;
}
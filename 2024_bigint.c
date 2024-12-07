#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "verify.h"
#include "operation.h"
#include "test.h"

int main()
{   
    //atexit(check_leaks);
    
    srand(time(NULL));
    // printf("============================================================\n");
    // printf("                   OKT Bignumber Library\n");
    // printf("============================================================\n");
    // printf("              All operations Time Measuring...\n");
    // bignum_time_all_test();
    // printf("============================================================\n");
    // printf("                     RSA Encryption...\n");

    /*********************************************
     * Accuracy Test : generate python file and run test
    **********************************************/
    // python_lshift_test("lshift_test.py");
    // python_rshift_test("rshift_test.py");
    // python_add_test("add_test.py");
    // python_sub_test("sub_test.py");
    // python_mul_test("mul_test.py");
    //python_mul_k_test("mul_k_test.py");
    //python_bin_div_test("bin_div_test.py");
    //python_squ_test("squ_test.py");
    //python_squ_k_test("squ_k_test.py");
    //python_l2r_test("l2r_test.py");
    //python_r2l_test("r2l_test.py");
    //python_MaS_test("MaS_test.py");
    python_bar_redu_test("bar_redu_test.py");
    //python_word_div_test("word_div_test.py");
    //python_naive_div_test("naive_div_test.py");
    return 0;
}
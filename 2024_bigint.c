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
    // printf("============================================================================\n");
    // printf("                           OKT Bignumber Library\n");
    // printf("============================================================================\n");
    // printf("                       All operations Time Measuring...\n");
    // bignum_time_all_test();
    printf("============================================================================\n");
    printf("                           RSA Encryption...\n");
    //compare_rsa_time_test(10);
    printf("============================================================================\n");

    /***********************************************************
     * Accuracy Test : generate python file and run test
    ************************************************************/
    // python_add_test("add_test.py");
    // printf("add_test.py completed\n");

    // python_sub_test("sub_test.py");
    // printf("sub_test.py completed\n");

    // python_mul_test("mul_test.py");
    // printf("mul_test.py completed\n");

    // python_mul_k_test("mul_kara_test.py");
    // printf("mul_kara_test.py completed\n");

    // python_bin_div_test("binary_div_test.py");
    // printf("binary_div_test.py completed\n");

    // python_word_div_test("word_div_test.py");
    // printf("word_div_test.py completed\n");

    // python_squ_test("squ_test.py");
    // printf("squ_test.py completed\n");

    // python_squ_k_test("squ_kara_test.py");
    // printf("squ_kara_test.py completed\n");

    // python_l2r_test("l2r_mod_exp_test.py");
    // printf("l2r_mod_exp_test.py completed\n");

    // python_r2l_test("r2l_mod_exp_test.py");
    // printf("r2l_mod_exp_test.py completed\n");

    // python_MaS_test("montgomery_ladder_mod_exp_test.py");
    // printf("montgomery_ladder_mod_exp_test.py completed\n");

    // python_bar_redu_test("barret_redu_test.py");
    // printf("barret_redu_test.py completed\n");

    python_rsa_key_gen_test("rsa_key_gen_test.py", 1);
    printf("rsa_key_gen_test.py completed\n");
    
    // python_rsa_enc_dec_test("rsa_enc_dec_test.py");
    // printf("rsa_enc_dec_test.py completed\n");
    // py_file_check();

    return 0;
}
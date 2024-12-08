#include <stdlib.h>

#include "verify.h"

void check_leaks(){

    #if defined(__APPLE__) || defined(__MACH__)
        system("leaks 2024_bigint");
    #endif
}

void py_file_check(){
    system("python add_test.py");
    system("python sub_test.py");
    system("python mul_test.py");
    system("python mul_kara_test.py");
    system("python binary_div_test.py");
    system("python word_div_test.py");
    system("python squ_test.py");
    system("python squ_kara_test.py");
    system("python l2r_mod_exp_test.py");
    system("python r2l_mod_exp_test.py");
    system("python montgomery_ladder_mod_exp_test.py");
    system("python barret_redu_test.py");
    system("python rsa_key_gen_test.py");
    system("python rsa_enc_dec_test.py");
}
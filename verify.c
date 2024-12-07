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
    system("python mul_k_test.py");
    system("python div_test.py");
    system("python squ_test.py");
    system("python squ_k_test.py");
    system("python l2r_test.py");
    system("python r2l_test.py");
    system("python MaS_test.py");
    system("python bar_redu_test.py");
    system("python word_div_test.py");
    system("python rsa_test.py");

}
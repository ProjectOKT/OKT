#include <stdlib.h>
#include <stdio.h>

#include "verify.h"

void check_leaks(){

    #if defined(__APPLE__) || defined(__MACH__)
        system("leaks " PROCESS_NAME);
    #endif
}

void run_system_command(const char *command) {
    int ret = system(command);
    if (ret == -1) {
        perror("Error executing system command");
        exit(EXIT_FAILURE);
    }
}

void py_file_check() {
    run_system_command("python add_test.py");
    run_system_command("python sub_test.py");
    run_system_command("python mul_test.py");
    run_system_command("python mul_kara_test.py");
    run_system_command("python binary_div_test.py");
    run_system_command("python word_div_test.py");
    run_system_command("python squ_test.py");
    run_system_command("python squ_kara_test.py");
    run_system_command("python l2r_mod_exp_test.py");
    run_system_command("python r2l_mod_exp_test.py");
    run_system_command("python montgomery_ladder_mod_exp_test.py");
    run_system_command("python barret_redu_test.py");
    run_system_command("python rsa_key_gen_test.py");
    run_system_command("python rsa_enc_dec_test.py");
}
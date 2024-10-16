#include <stdlib.h>

#include "verify.h"
void check_leaks(){

    #if defined(_WIN32) || defined(_WIN64)
        system("drmemory -- 2024_bigint.exe");
    #elif defined(__APPLE__) || defined(__MACH__)
        system("leaks 2024_bigint");
    #else
        fprintf(stderr, ERR_NOT_SUPPORT_OS);
    #endif
}
#include <stdlib.h>

#include "verify.h"

void check_leaks(){

    #if defined(_WIN32) || defined(_WIN64)
        fprintf(stderr, ERR_NOT_SUPPORT_OS);
    #elif defined(__APPLE__) || defined(__MACH__)
        system("sudo leaks /MacOs/bigint_app");
    #else
        fprintf(stderr, ERR_NOT_SUPPORT_OS);
    #endif
}
#include <stdlib.h>

#include "verify.h"

void check_leaks(){

    #if defined(__APPLE__) || defined(__MACH__)
        system("leaks 2024_bigint");
    #endif
}
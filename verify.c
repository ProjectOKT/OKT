#include <stdlib.h>

#include "verify.h"
void check_leaks(){
    system("leaks 2024_bigint");
}
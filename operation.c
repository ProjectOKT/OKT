#include <stdio.h>


#include "operation.h"
#include "bigintfun.h"
#include "params.h"

msg bi_add_same_sign(bigint** dst, bigint* src1, bigint* src2){
    //더 큰 수 비교
    if (bi_compare(src1, src2) == POSITIVE){
        int max_len = src1->word_len;
        for(int idx = 0; idx < max_len; idx){
            
        }
    }

}
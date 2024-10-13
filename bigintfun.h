#pragma once

#include "dtype.h"

/* big int <- array */
msg bi_set_from_array(bigint** dst, int sign, int word_len, word* a);

/* str = 0x123qqppwq(숫자가 아닌 경우)에 대한 예외 처리 필요 */
msg bi_set_from_string(bigint** dst,  int sign, char* int_str, int base);

/* A[4] = {1,2,3,0} -> {1.2.3.*1*} */
// 마지막 배열은 nonzero라는 보장이 필요 word_len을 맞추기 위해
msg bi_get_random(bigint** dst, int word_len);

// 포인터로 하지않으면 구조체가 다 복사되서 넘어가기 때문에 메모리적으로 포인터가 더효율적
msg bi_print(bigint** dst, int base); // 현재는 16진수와 2진수 출력만 하기

msg bi_new(bigint** dst, int word_len);
void array_init(word* a, int word_len);
msg bi_delete(bigint** dst); // 반납시에 비밀값은 0으로 씌우고 지워야함
void array_copy(word* src_arr, word* dst_arr, int array_len);
msg bi_refine(bigint* dst);

/* tmp <- x */
msg bi_assign(bigint** dst, bigint* src);
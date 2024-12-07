#include <stdio.h>
#include <stdlib.h>

#include "bigintfun.h"
#include "params.h"
#include "errormsg.h"
#include "operation_tool.h"
#include "operation.h"
//(min) return smaller a and b
//(max) return bigger  a and b
#define min(a,b)  ((a) <= (b) ? (a) : (b))
#define max(a,b)  ((a) >= (b) ? (a) : (b))

/***********************************************
 * Addition
 ***********************************************/
/**
 * @brief Adds two words with a carry value.
 * 
 * This function computes the sum of two `word` values (`src1` and `src2`) along 
 * with a carry value. It returns the result of the addition and updates the carry 
 * pointer to reflect any overflow.
 * 
 * @param[in] src1 The first `word` to be added.
 * @param[in] src2 The second `word` to be added.
 * @param[in,out] c Pointer to an integer representing the carry. This value 
 *                  is updated to reflect any overflow after the addition.
 * 
 * @return The result of the addition of `src1`, `src2`, and the carry.
 */
word add_c(IN word src1, IN word src2, IN int* c)
{
    word result = src1 + src2;
    int cout = 0;
    if (result < src1){
        cout = 1;
    }
    result += *c;
    if(result < (word)*c){
        cout += 1;
    }
    *c = cout;
    return result;
}

/**
 * @brief Adds two bigint values with the same sign.
 * 
 * This function adds two `bigint` structures (`src1` and `src2`) that are both
 * either positive or negative. The result is stored in a newly allocated `bigint`
 * structure pointed to by `dst`. The function ensures that the resulting bigint
 * has the appropriate length and sign.
 * 
 * @param[out] dst Pointer to a pointer of the resulting `bigint` after addition.
 * @param[in] src1 Pointer to the first `bigint` to be added.
 * @param[in] src2 Pointer to the second `bigint` to be added. 
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg add_same_sign(OUT bigint** dst, IN bigint* src1, IN bigint* src2)
{
    msg error_msg = 0;
    word result;
    int max_len;
    int c = 0;
    
    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
        if(error_msg == FAILED )
        {
            return FAILED;
        }
    }

    if(src1->sign == POSITIVE){     //dst->word_len = longer bigint(not bigger)-> word_len  
        max_len = src1->word_len;
        error_msg = bi_new(dst, max_len + 1);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
        (*dst)->sign = POSITIVE;
    }
    else{
        max_len = src2->word_len;
        error_msg = bi_new(dst, max_len + 1);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
        (*dst)->sign = NEGATIVE;          
    }

    if((src1->word_len) > (src2->word_len)){
        error_msg = bi_fillzero(src2, src1->word_len, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }
    else{
        error_msg = bi_fillzero(src1, src2->word_len, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }

    for(int idx = 0; idx < max_len; idx++){    
        result = add_c(src1->a[idx], src2->a[idx], &c);
        (*dst)->a[idx] = result;
    }
    if(c == 1){
        (*dst)->a[max_len] = 1;     //If carry = 1, word_len += 1
    }
    else{
        error_msg = bi_refine(*dst);
    }
    if(error_msg == FAILED)
    {
        return FAILED;
    }

    return SUCCESS;
}

/**
 * @brief Adds two bigint values with the same sign and stores value to operator.
 * 
 * This function adds two `bigint` structures (`src1` and `src2`) that are both
 * either positive or negative. The result is stored in a newly allocated `bigint`
 * structure pointed to by `dst`. The function ensures that the resulting bigint
 * has the appropriate length and sign.
 * 
 * @param[out] dst Pointer Pointer to the first `bigint` to be added and stored result
 * @param[in] src1 Pointer to the second `bigint` to be added.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg add_same_sign_replace(INOUT bigint** dst, IN bigint* src1)
{
    msg error_msg = 0;
    word result;
    int max_len;
    int c = 0;
    
    bigint *temp_dst = NULL;
    
    bi_assign(&temp_dst, *dst);     //dst copy

    if(src1->sign == POSITIVE){   
        max_len = src1->word_len;
        error_msg = bi_new(dst, max_len + 1);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
        (*dst)->sign = POSITIVE;
    }
    else{
        max_len = temp_dst->word_len;
        error_msg = bi_new(dst, max_len + 1);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
        (*dst)->sign = NEGATIVE;
    }

    if((src1->word_len) > (temp_dst->word_len)){
        error_msg = bi_fillzero(temp_dst, src1->word_len, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }
    else{
        error_msg = bi_fillzero(src1, temp_dst->word_len, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }

    for(int idx = 0; idx < max_len; idx++){    
        result = add_c(src1->a[idx], temp_dst->a[idx], &c);
        (*dst)->a[idx] = result;
    }
    if(c == 1){
        (*dst)->a[max_len] = 1;
    }
    else{
        error_msg = bi_refine(*dst);
    }
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    bi_delete(&temp_dst);
    return SUCCESS;
}

/***********************************************
 * Subtraction
 ***********************************************/
/**
 * @brief Subtracts two words with borrow handling.
 * 
 * This function performs the subtraction of two words, `A` and `B`, taking into 
 * account a borrow value. It updates the borrow status and returns the result of 
 * the subtraction.
 * 
 * @param[in] A The first word from which the borrow-adjusted `B` will be subtracted.
 * @param[in,out] borrow A pointer to the current borrow value, which will be updated.
 * @param[in] B The second word to be subtracted from `A` after adjusting for borrow.
 * 
 * @return The result of the subtraction of `B` from `A`, adjusted for borrow.
 */
word sub_adb(IN word A, IN char* borrow, IN word B)
{
    char borrow_buf = 0;
    word C = A - (*borrow);

    if(A < (word)*borrow)
    {
        borrow_buf = 1;
    }

    if(C < B)
    {
        borrow_buf += 1;
    }

    C = C - B;

    *borrow = borrow_buf;
    return C;
}

/**
 * @brief Subtracts one bigint from another with borrow handling.
 * 
 * This function performs the subtraction of two big integers (`src1` and `src2`), 
 * taking into account any borrows that occur during the subtraction process. 
 * The result is stored in a newly allocated bigint pointed to by `dst`.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the subtraction.
 * @param[in] src1 The minuend (the bigint from which `src2` will be subtracted).
 * @param[in] src2 The subtrahend (the bigint to be subtracted from `src1`).
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_subc(OUT bigint** dst, IN bigint* src1, IN bigint* src2)
{
    msg error_msg = 0;
    error_msg = bi_fillzero(src2, src1->word_len, TOP);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    
    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
        if(error_msg == FAILED )
        {
            return FAILED;
        }
    }

    error_msg = bi_new(dst, src1->word_len);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    (*dst)->sign = POSITIVE;
    
    char borrow = 0;

    for (int index = 0; index<(src2->word_len); index++)
    {
        (*dst)->a[index] = sub_adb(src1->a[index], &borrow, src2->a[index]);
    }
    
    return bi_refine(*dst);
}

/***********************************************
 * Muliplication
 ***********************************************/
/**
 * @brief Multiplication two single words
 * 
 * This function performs multiplication between two words (`src1` and `src2`) and 
 * stores the result in a bigint structure pointed to by `dst`. It handles the multiplication
 * by dividing each word into half-word, then products and adds each others.
 * 
 * @param[out] dst Pointer to the result bigint that will store the result of the multiplication.
 *                 The function allocates memory for this bigint and initializes its elements.
 * @param[in] src1 The first operand for the multiplication.
 * @param[in] src2 The second operand for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 * 
 */
msg bi_smul(OUT bigint** dst, IN word src1, IN word src2)
{
    int error_msg = 0;

    error_msg = bi_new(dst, 2);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    (*dst)->sign = POSITIVE;

    #if SIZEOFWORD == 8
        word A1 = 0, A0 = 0, B1 = 0, B0 = 0;
        word temp, temp1 = 0, temp0 = 0;
        A1 = src1 >> (SIZEOFWORD / 2);
        A0 = src1 & (((word)1 << (SIZEOFWORD / 2)) - 1);
        
        B1 = src2 >> (SIZEOFWORD / 2);
        B0 = src2 & (((word)1 << (SIZEOFWORD / 2)) - 1);

        temp1 = (word)A1 * (word)B0;
        temp0 = (word)A0 * (word)B1;
        temp0 += temp1;
        temp1 = (temp0 < temp1);

        (*dst)->a[1] = (word)A1 * (word)B1;
        temp = (*dst)->a[0] = (word)A0 * (word)B0;
        
        (*dst)->a[0] += temp0 << (SIZEOFWORD / 2);
        (*dst)->a[1] += (temp1 << (SIZEOFWORD / 2)) + (temp0 >> (SIZEOFWORD / 2)) + ((*dst)->a[0] < temp);
        
        return SUCCESS;

    #else
        half_word A1 = 0, A0 = 0, B1 = 0, B0 = 0;
        word temp, temp1 = 0, temp0 = 0;

        A1 = src1 >> (sizeof(half_word) * 8);
        A0 = src1 & (((word)1 << (sizeof(half_word) * 8)) - 1);

        B1 = src2 >> (sizeof(half_word) * 8);
        B0 = src2 & (((word)1 << (sizeof(half_word) * 8)) - 1);

        temp1 = (word)A1 * (word)B0;
        temp0 = (word)A0 * (word)B1;
        temp0 += temp1;
        temp1 = (temp0 < temp1);

        (*dst)->a[1] = (word)A1 * (word)B1;
        temp = (*dst)->a[0] = (word)A0 * (word)B0;
        
        (*dst)->a[0] += temp0 << (sizeof(half_word) * 8);
        (*dst)->a[1] += (temp1 << (sizeof(half_word) * 8)) + (temp0 >> (sizeof(half_word) * 8)) + ((*dst)->a[0] < temp);
        
        return SUCCESS;
    #endif
}

/**
 * @brief Multiplication two multi-word size integers with the non-negative integer
 * 
 * This function performs the Multiplication of two big non-negative integers (`src1` and `src2`), 
 * This Improved Multiplication performs single words mul by smul and connects result of smul.
 * The result is addtion of the results connected sigle words mul with shifting and zero padding.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the non-negative multiplication.
 * @param[in] src1 The first operand for the multiplication.
 * @param[in] src2 The second operand for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mulc(OUT bigint** dst, IN bigint* src1, IN bigint* src2)
{   
    int error_msg = 0;
    bigint* temp0 = NULL;
    bigint* temp1 = NULL;
    bigint* temp = NULL;
    bigint* tempC = NULL;
    bigint* tempC_result = NULL;
    bigint* tempT0 = NULL;
    bigint* tempT1 = NULL;
    bigint* tempT0_result = NULL;
    bigint* tempT1_result = NULL;

    if(error_msg == FAILED)
    {
        return FAILED;
    }

    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }

    error_msg = bi_new(&tempC, 1);
    tempC->sign = POSITIVE;

    if((src1->word_len) % 2 == 1)
    {
        error_msg = bi_fillzero(src1, src1->word_len + 1, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }   
    }
    if((src2->word_len) % 2 == 1)
    {
        error_msg = bi_fillzero(src2, src2->word_len + 1, TOP);
        if(error_msg == FAILED)
        {
            return FAILED;
        }
    }
    for(int idx2 = 0; idx2 < src2->word_len; idx2++){
        bi_new(&tempT1, 1);
        tempT0 = NULL;
        for(int idx1 = 0; idx1 < (src1->word_len)/ 2; idx1++){
            bi_smul(&temp0, src1->a[2*idx1], src2->a[idx2]);
            bi_smul(&temp1, src1->a[2*idx1 + 1], src2->a[idx2]);
            bi_connect(&tempT0_result, temp0, tempT0);
            bi_connect(&tempT1_result, temp1, tempT1);
            bi_assign(&tempT0, tempT0_result);
            bi_assign(&tempT1, tempT1_result);

            bi_delete(&tempT0_result);
            bi_delete(&tempT1_result);
            bi_delete(&temp0);
            bi_delete(&temp1);
        }
        if (bi_compare(tempT1, tempT0) == 1){
            add_same_sign(&temp, tempT1, tempT0);

            bi_delete(&tempT1);
            bi_delete(&tempT0);
        }
        else{
            add_same_sign(&temp, tempT0, tempT1);

            bi_delete(&tempT1);
            bi_delete(&tempT0);
        }
        bi_fillzero(temp, temp->word_len + idx2, BOTTOM);
        if (bi_compare(temp, tempC) == 1){
            add_same_sign(&tempC_result, temp, tempC);
        }
        else
        {
            add_same_sign(&tempC_result, tempC, temp);
        }
        bi_assign(&tempC, tempC_result);
    }


    bi_assign(dst, tempC);
    bi_delete(&tempC);
    bi_delete(&temp);
    bi_delete(&tempC_result);
    bi_delete(&tempT0);
    bi_delete(&tempT1);
    return SUCCESS;
}

/**
 * @brief Karatsuba Multiplication two big integers
 * 
 * This function performs the Karatsuba Multiplication of two big integers (`src1` and `src2`), 
 * This Multiplication performs multiplication by Karatsuba Multiplication.
 * Consider sign of two integers, as the result of the muliplication with two negative integers is positive.
 * 
 * @param[out] dst Pointer to the result bigint that will hold the result of the multiplication.
 * @param[in] src1 The first big integer for the multiplication.
 * @param[in] src2 The second big integer for the multiplication.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_mul_k(OUT bigint** dst, IN const bigint* src1, IN const bigint* src2)
{
    bigint* temp_src1 = NULL;
    bigint* temp_src2 = NULL;
    
    bi_assign(&temp_src1, src1);
    bi_assign(&temp_src2, src2);
    temp_src1->sign = POSITIVE;
    temp_src2->sign = POSITIVE;

    int n = src1->word_len;
    int m = src2->word_len;

    //flag
    if (KARA_FLAG_MUL >= min(n,m)) {
        bi_mul(dst,temp_src1,temp_src2);
        bi_delete(&temp_src1);
        bi_delete(&temp_src2);
        return SUCCESS;
    }

    bigint* a1 = NULL;
    bigint* a0 = NULL; 
    bigint* b1 = NULL;
    bigint* b0 = NULL; 
    bigint* t1 = NULL;
    bigint* t0 = NULL;
    bigint* r = NULL;
    bigint* s1 = NULL;
    bigint* s0 = NULL;
    bigint* s = NULL;
    bigint* temp = NULL;
    bigint* sum_s = NULL;

    int l = (max(n,m) + 1) >> 1;
    int lw = l*SIZEOFWORD;
    // a >> lw
    bi_assign(&a1, temp_src1);
    bi_bit_rshift(a1,lw);
    //a mod 
    bi_assign(&a0, temp_src1);
    if (a0->word_len > l){
        for (int i = l; i < a0->word_len; i++)
        {
            a0->a[i] = 0;
        }
    }
    
    bi_delete(&temp_src1);
    
    // b >> lw
    bi_assign(&b1, temp_src2);
    bi_bit_rshift(b1,lw);
    //b mod 
    bi_assign(&b0, temp_src2);
    if (b0->word_len > l){
        for (int i = l; i < b0->word_len; i++)
        {
            b0->a[i] = 0;
        }
    }
    bi_delete(&temp_src2);
    bi_refine(a0);
    bi_refine(b0);
    bi_refine(a1);
    bi_refine(b1);
    // t1, t0
    bi_mul_k(&t1, a1, b1);
    bi_mul_k(&t0, a0, b0);
    
    // r = (t1 << 2*lw) + t0
    bi_assign(&temp, t1);
    bi_bit_lshift(temp,2*lw);
    bi_add(&r, temp, t0);
    
    // s1 = a0 - a1
    bi_sub(&s1,a0,a1);
    bi_delete(&a1);
    bi_delete(&a0);
    // s0 = b1 - b0
    bi_sub(&s0,b1,b0);
    bi_delete(&b1);
    bi_delete(&b0);
    //24,25
    int s_sign = 0;
    if ((s1->sign) == (s0->sign)){
        s_sign = POSITIVE;
    }
    else {
        s_sign = NEGATIVE;
    }
    s1->sign = POSITIVE;
    s0->sign = POSITIVE;
    bi_mul_k(&s,s1,s0);
    bi_delete(&s0);
    bi_delete(&s1);
    s->sign = s_sign;
    //s = s + t1
    bi_add(&temp,s,t1);

    bi_delete(&t1);
    bi_delete(&s);
    //s = s + t0
    bi_add(&sum_s,temp,t0);

    bi_delete(&temp);
    bi_delete(&t0);
    //s = s << lw
    bi_bit_lshift(sum_s,lw);
    bi_add(dst,r,sum_s);
    bi_delete(&sum_s);
    bi_delete(&r);

    return SUCCESS;
}

/***********************************************
 * Division
 ***********************************************/
/**
 * @brief Binary long division of two big integers.
 * 
 * This function performs binary long division of two big integers (`src1` and `src2`), computing both the quotient and remainder.
 * The division is performed bit-by-bit, starting from the most significant bit of the dividend. 
 * The function assumes that the divisor (`src2`) is positive and that the dividend (`src1`) is greater than or equal to the divisor.
 * 
 * The `quotient` is always positive, and the `remainder` is adjusted to its correct value. If the remainder is zero, 
 * its sign is explicitly set to `ZERO`.
 * 
 * If any error occurs (e.g., invalid input or memory allocation failure), the function returns an error.
 * 
 * @param[out] quotient Pointer to the result bigint that will hold the quotient of the division.
 * @param[out] remainder Pointer to the result bigint that will hold the remainder of the division.
 * @param[in] src1 The dividend big integer for the division.
 * @param[in] src2 The divisor big integer for the division.
 * 
 * @return Returns 1 on success, -1 on failure (e.g., invalid input or memory allocation error).
 */
msg bi_binary_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* src1, IN const bigint* src2)
{
    int error_msg = FAILED;
    int word_bit_size = 0;
    int divc_num = 0;

    if (src1 == NULL || src2 == NULL || !((src2->sign == POSITIVE) && (bi_compare(src1, src2) >= 0)))
    {
        fprintf(stderr, ERR_INVALID_INPUT);
        return FAILED;
    }

    word_bit_size = sizeof(word) * 8;
    divc_num = (src1->word_len * word_bit_size) - 1;

    error_msg = bi_new(quotient, src1->word_len - src2->word_len + 1);
    if (error_msg == FAILED)
    {
        return FAILED;
    }
    (*quotient)->sign = POSITIVE;

    error_msg = bi_new(remainder, 1);
    if (error_msg == FAILED)
    {
        return FAILED;
    }
    (*remainder)->sign = POSITIVE;

    for(int bitindex = divc_num; bitindex >= 0; bitindex--)
    {   
        error_msg = bi_bit_lshift(*remainder, 1);
        if (error_msg == FAILED)
        {
            return FAILED;
        }

        (*remainder)->a[0] ^= (src1->a[bitindex / word_bit_size] >> ((bitindex % word_bit_size)) & (0x01));
        if (bi_compare(*remainder, src2) >= 0)
        {
            (*quotient)->a[bitindex / word_bit_size] ^= (word)1<<((bitindex % word_bit_size));

            error_msg = bi_sub(remainder, *remainder, src2);
            if(error_msg == FAILED)
            {
                return FAILED;
            }
            (*remainder)->sign = POSITIVE;
        }
    }
    error_msg = bi_refine(*quotient);
    if(error_msg == FAILED)
    {
        return FAILED;
    }
    if((*remainder)->word_len == 1 && (*remainder)->a[0] == 0)
    {
        (*remainder)->sign = ZERO;
    }

    return SUCCESS;
}

/***********************************************
 * Square
 ***********************************************/
/**
 * @brief Squaring of single word.
 * 
 * This function performs Squaring of single word (`src1`)
 * The sign of the result is always POSITIVE.
 * 
 * @param[out] dst Pointer to the result bigint that squared by src1.
 * @param[in] src1 The single word for the squaring.
 * 
 * @return Returns 1 on success, -1 on failure.
 */
msg bi_squc(OUT bigint** dst, IN const word src1)
{   
    int error_msg = 0;
    word A1 = 0, A0 = 0;
    bigint* T = NULL;
    bigint* C = NULL;

    if((*dst) != NULL)
    {
        error_msg = bi_delete(dst);
    }
    
    error_msg = bi_new(dst, 2);
    error_msg = bi_new(&C, 2);

    C->sign = POSITIVE;

    error_msg = bi_new(&T, 1);

    T->sign = POSITIVE;

    #if SIZEOFWORD == 8
        A1 = src1 >> (SIZEOFWORD/2);
        A0 = src1 & (((word)1 << (SIZEOFWORD/2)) - 1);
    #else
        A1 = src1 >> (sizeof(half_word) * 8);
        A0 = src1 & (((word)1 << (sizeof(half_word) * 8)) - 1);
    #endif

    C->a[1] = (A1*A1);
    C->a[0] = (A0*A0);
    T->a[0] = A0*A1;
    error_msg = bi_bit_lshift(T, SIZEOFWORD/2 + 1);

    error_msg = add_same_sign(dst, C, T);

    bi_delete(&C);
    bi_delete(&T);

    if(error_msg == FAILED )
    {
        return FAILED;
    }

    return SUCCESS;
}


msg bi_word_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B)
{
    int n = A->word_len;
    bi_new(remainder,1);
    
    bi_new(quotient,n);
    (*quotient)->sign = POSITIVE;

    bigint* temp = NULL;
    
    for (int i = n - 1; i >= 0; i--){
        //R(i+1)W+Ai
        bi_assign((&temp),(*remainder));
        bi_bit_lshift(temp,SIZEOFWORD);
        temp->a[0] = A->a[i]; 
        temp->sign = POSITIVE;
        bi_refine(temp);
        bi_divc((&(*quotient)->a[i]), remainder, temp, B);
    }
    bi_refine(*quotient);

    bi_delete(&temp);
    return SUCCESS;
}


msg bi_divc(OUT word* quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B)
{
    if (bi_compare(A,B) == -1){
        (*quotient) = 0;
        bi_assign(remainder,A);
        return SUCCESS;
    }
    int m = B->word_len;
    word Bm_1 = B->a[m-1];
    word two_exp_w_1 = ((word)1) << (SIZEOFWORD - 1);
    int k = 0;
    while (Bm_1 < two_exp_w_1){
        Bm_1 = Bm_1 << 1;
        k++;
    }
    bigint* temp_A = NULL;
    bigint* temp_B = NULL;
    bi_assign(&temp_A,A);
    bi_assign(&temp_B,B);
    bi_bit_lshift(temp_A,k);
    bi_bit_lshift(temp_B,k);
    
    bi_divcc(quotient,remainder,temp_A,temp_B);

    bi_bit_rshift((*remainder),k);

    bi_delete(&temp_A);
    bi_delete(&temp_B);
    return SUCCESS;
}


msg bi_divcc(OUT word* quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B)
{
    int n = A->word_len;
    int m = B->word_len;

    bigint* BQ = NULL;
    bigint* Q = NULL;
    bigint* temp = NULL;
    
    word Am = A->a[m];
    word Am_1 = A->a[m-1];
    word Bm_1 = B->a[m-1];
    word W_1 = max_word;

    if (n == m){
        (*quotient) = Am_1 / Bm_1; 
    }

    if (n == (m + 1)){
        if(Am == Bm_1){
            (*quotient) = W_1; 
        }
        else{
            bigint* smallA = NULL;
            bi_new(&smallA,2);
            smallA->sign = POSITIVE;
            smallA->a[0] = Am_1;
            smallA->a[1] = Am;
            bi_2_word_div(quotient, smallA, Bm_1);
            bi_delete(&smallA);
        }
    }

    bi_new(&Q,1);
    Q->a[0] = (*quotient);
    Q->sign = POSITIVE;
    
    bi_mul_k(&BQ,B,Q);
    bi_sub(remainder,A,BQ);
    
    while((*remainder)->sign == NEGATIVE){
        (*quotient)--;
        //bi_assign(&temp,(*remainder));
        bi_add_replace(remainder,B);
    }

    bi_delete(&temp);
    bi_delete(&BQ);
    bi_delete(&Q);
    return SUCCESS;
}


msg bi_2_word_div(OUT word* quotient,  IN const bigint* A, IN const word B)
{
    (*quotient) = 0;

    word remainder = A->a[1];
    word two_exp_w_1 = ((word)1) << (SIZEOFWORD - 1);
    word A0 = A->a[0];

    for (int j  = SIZEOFWORD-1; j >=0; j--){
        int aj = ((A0 >> j) & 1);
        word two_j = (((word)1) << j);
        if (remainder >= two_exp_w_1){
            (*quotient) += two_j;
            //(B-R)
            word temp = B - remainder;
            //R+aj
            remainder += aj;
            // R+aj - (B-R)
            remainder -= temp;
        }
        else{
            remainder = (remainder << 1) + aj;
            if (remainder >= B){
                (*quotient) += two_j;
                remainder -= B;
            }
        }
    }
    return SUCCESS;
}


msg bi_naive_long_division(OUT bigint** quotient, OUT bigint** remainder, IN const bigint* A, IN const bigint* B)
{
    bigint* one = NULL;
    bi_new(&one,1);
    one->sign=POSITIVE;
    one->a[0] = 1;

    bi_new(quotient,1);
    
    bi_assign(remainder,A);

    while(bi_compare((*remainder),B) != -1){      
        bi_add_replace(quotient,one);
        bi_sub(remainder,(*remainder),B);
    }
    bi_delete(&one);
    return SUCCESS;
}
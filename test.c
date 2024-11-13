#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bigintfun.h"
#include "arrayfun.h"
#include "dtype.h"
#include "errormsg.h"
#include "params.h"
#include "verify.h"
#include "operation.h"

/**
 * @brief Runs a specific addition test from a file for validation.
 *
 * This function reads test cases from the specified file and executes an addition test based on the provided test number. 
 * It is commonly used for validating the correctness of bigint addition operations.
 *
 * @param filename The name of the file containing test cases.
 * @param testnum The specific test case number to run from the file.
 * @return void
 */
void sage_add_test(const char* filename, int testnum) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    for (int i = 0; i < testnum; i++) {
        //인자
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % 10 + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % 10 + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % 10 + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % 10 + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        //0이 아닌 결과
        bigint *pp_add = NULL;
        bi_add(&pp_add, pos_a, pos_b);

        bigint *nn_add = NULL;
        bi_add(&nn_add, neg_c, neg_d);

        bigint *pn_add = NULL;
        bi_add(&pn_add, pos_a, neg_d);

        bigint *np_add = NULL;
        bi_add(&np_add, neg_c, pos_b);
        
        //0일때
        bigint *pz_add = NULL;
        bi_add(&pz_add, pos_b, z);

        bigint *nz_add = NULL;
        bi_add(&nz_add, neg_c, z);

        bigint *zp_add = NULL;
        bi_add(&zp_add, z, pos_b);

        bigint *zn_add = NULL;
        bi_add(&zn_add, z, neg_c);

        bigint *zz_add = NULL;
        bi_add(&zz_add, z, z);

        //
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_add = ");
        bi_fprint(file,pp_add);
        fprintf(file, "nn_add = ");
        bi_fprint(file,nn_add);
        fprintf(file, "np_add = ");
        bi_fprint(file,np_add);
        fprintf(file, "pn_add = ");
        bi_fprint(file,pn_add);

        fprintf(file, "zp_add = ");
        bi_fprint(file,zp_add);
        fprintf(file, "zn_add = ");
        bi_fprint(file,zn_add);
        fprintf(file, "nz_add = ");
        bi_fprint(file,nz_add);
        fprintf(file, "pz_add = ");
        bi_fprint(file,pz_add);
        fprintf(file, "zz_add = ");
        bi_fprint(file,zz_add);

        fprintf(file, "if (pos_a + pos_b != pp_add):\n \t print(f\"[pp_add]: {pos_a:#x} + {pos_b:#x} != {pp_add:#x}\\n\")\n");
        fprintf(file, "if (neg_c + neg_d != nn_add):\n \t print(f\"[nn_add]: {neg_c:#x} + {neg_d:#x} != {nn_add:#x}\\n\")\n");
        fprintf(file, "if (pos_a + neg_d != pn_add):\n \t print(f\"[pn_add]: {pos_a:#x} + {neg_d:#x} != {pn_add:#x}\\n\")\n");
        fprintf(file, "if (neg_c + pos_b != np_add):\n \t print(f\"[np_add]: {neg_c:#x} + {pos_b:#x} != {np_add:#x}\\n\")\n");

        fprintf(file, "if (pos_b + z != pz_add):\n \t print(f\"[pz_add]: {pos_b:#x} + {z:#x} != {pz_add:#x}\\n\")\n");
        fprintf(file, "if (neg_c + z != nz_add):\n \t print(f\"[nz_add]: {neg_c:#x} + {z:#x} != {nz_add:#x}\\n\")\n");
        fprintf(file, "if (z + pos_b != zp_add):\n \t print(f\"[zp_add]: {z:#x} + {pos_b:#x} != {zp_add:#x}\\n\")\n");
        fprintf(file, "if (z + neg_c != zn_add):\n \t print(f\"[zn_add]: {z:#x} + {neg_c:#x} != {zn_add:#x}\\n\")\n");
        fprintf(file, "if (z + z != zz_add):\n \t print(f\"[zz_add]: {z:#x} + {z:#x} != {zz_add:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_add);
        bi_delete(&nn_add);
        bi_delete(&pn_add);
        bi_delete(&np_add);

        bi_delete(&pz_add);
        bi_delete(&zn_add);
        bi_delete(&nz_add);
        bi_delete(&zp_add);
        bi_delete(&zz_add);
    }   
    fclose(file);
}


/**
 * @brief Runs a specific subtraction test from a file for validation.
 *
 * This function reads test cases from the specified file and executes a subtraction test based on the provided test number.
 * It is commonly used for validating the correctness of bigint subtraction operations.
 *
 * @param filename The name of the file containing test cases.
 * @param testnum The specific test case number to run from the file.
 * @return void
 */
void sage_sub_test(const char* filename, int testnum) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    for (int i = 0; i < testnum; i++) {
        //인자
        bigint *pos_a = NULL;
        bi_get_random(&pos_a,POSITIVE, rand() % 63 + 1);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b,POSITIVE, rand() % 63 + 1);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c,NEGATIVE, rand() % 63 + 1);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d,NEGATIVE, rand() % 63 + 1);
        bigint *z = NULL;
        bi_new(&z,1);

        //0이 아닌 결과
        bigint *pp_sub = NULL;
        bi_sub(&pp_sub, pos_a, pos_b);

        bigint *nn_sub = NULL;
        bi_sub(&nn_sub, neg_c, neg_d);

        bigint *pn_sub = NULL;
        bi_sub(&pn_sub, pos_a, neg_d);

        bigint *np_sub = NULL;
        bi_sub(&np_sub, neg_c, pos_b);
        
        //0일때
        bigint *pz_sub = NULL;
        bi_sub(&pz_sub, pos_b, z);

        bigint *nz_sub = NULL;
        bi_sub(&nz_sub, neg_c, z);

        bigint *zp_sub = NULL;
        bi_sub(&zp_sub, z, pos_b);

        bigint *zn_sub = NULL;
        bi_sub(&zn_sub, z, neg_c);

        bigint *zz_sub = NULL;
        bi_sub(&zz_sub, z, z);

        //
        fprintf(file, "pos_a = ");
        bi_fprint(file,pos_a);
        fprintf(file, "pos_b = ");
        bi_fprint(file,pos_b);
        fprintf(file, "neg_c = ");
        bi_fprint(file,neg_c);
        fprintf(file, "neg_d = ");
        bi_fprint(file,neg_d);
        fprintf(file, "z = ");
        bi_fprint(file,z);

        fprintf(file, "pp_sub = ");
        bi_fprint(file,pp_sub);
        fprintf(file, "nn_sub = ");
        bi_fprint(file,nn_sub);
        fprintf(file, "np_sub = ");
        bi_fprint(file,np_sub);
        fprintf(file, "pn_sub = ");
        bi_fprint(file,pn_sub);

        fprintf(file, "zp_sub = ");
        bi_fprint(file,zp_sub);
        fprintf(file, "zn_sub = ");
        bi_fprint(file,zn_sub);
        fprintf(file, "nz_sub = ");
        bi_fprint(file,nz_sub);
        fprintf(file, "pz_sub = ");
        bi_fprint(file,pz_sub);
        fprintf(file, "zz_sub = ");
        bi_fprint(file,zz_sub);

        fprintf(file, "if (pos_a - pos_b != pp_sub):\n \t print(f\"[pp_sub]: {pos_a:#x} + {pos_b:#x} != {pp_sub:#x}\\n\")\n");
        fprintf(file, "if (neg_c - neg_d != nn_sub):\n \t print(f\"[nn_sub]: {neg_c:#x} + {neg_d:#x} != {nn_sub:#x}\\n\")\n");
        fprintf(file, "if (pos_a - neg_d != pn_sub):\n \t print(f\"[pn_sub]: {pos_a:#x} + {neg_d:#x} != {pn_sub:#x}\\n\")\n");
        fprintf(file, "if (neg_c - pos_b != np_sub):\n \t print(f\"[np_sub]: {neg_c:#x} + {pos_b:#x} != {np_sub:#x}\\n\")\n");

        fprintf(file, "if (pos_b - z != pz_sub):\n \t print(f\"[pz_sub]: {pos_b:#x} - {z:#x} != {pz_sub:#x}\\n\")\n");
        fprintf(file, "if (neg_c - z != nz_sub):\n \t print(f\"[nz_sub]: {neg_c:#x} - {z:#x} != {nz_sub:#x}\\n\")\n");
        fprintf(file, "if (z - pos_b != zp_sub):\n \t print(f\"[zp_sub]: {z:#x} - {pos_b:#x} != {zp_sub:#x}\\n\")\n");
        fprintf(file, "if (z - neg_c != zn_sub):\n \t print(f\"[zn_sub]: {z:#x} - {neg_c:#x} != {zn_sub:#x}\\n\")\n");
        fprintf(file, "if (z - z != zz_sub):\n \t print(f\"[zz_sub]: {z:#x} - {z:#x} != {zz_sub:#x}\\n\")\n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_sub);
        bi_delete(&nn_sub);
        bi_delete(&pn_sub);
        bi_delete(&np_sub);

        bi_delete(&pz_sub);
        bi_delete(&zn_sub);
        bi_delete(&nz_sub);
        bi_delete(&zp_sub);
        bi_delete(&zz_sub);
    }   
    fclose(file);
}

void sage_mul_test(const char* filename, int testnum) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    for (int i = 0; i < testnum; i++) {
        //인자
        bigint *pos_a = NULL;
        bi_get_random(&pos_a, POSITIVE, 4);
        bigint *pos_b = NULL;
        bi_get_random(&pos_b, POSITIVE, 4);
        bigint *neg_c = NULL;
        bi_get_random(&neg_c, NEGATIVE, 4);
        bigint *neg_d = NULL;
        bi_get_random(&neg_d, NEGATIVE, 4);
        bigint *z = NULL;
        bi_new(&z, 1);

        //0이 아닌 결과
        bigint *pp_sub = NULL;
        bi_new(&pp_sub, 4);
        bi_sub(&pp_sub, pos_a, pos_b);  // 뺄셈 수행

        bigint *nn_sub = NULL;
        bi_new(&nn_sub, 4);
        bi_sub(&nn_sub, neg_c, neg_d);  // 뺄셈 수행

        bigint *pn_sub = NULL;
        bi_new(&pn_sub, 4);
        bi_sub(&pn_sub, pos_a, neg_d);  // 뺄셈 수행

        bigint *np_sub = NULL;
        bi_new(&np_sub, 4);
        bi_sub(&np_sub, neg_c, pos_b);  // 뺄셈 수행

        //0일때
        bigint *pz_sub = NULL;
        bi_new(&pz_sub, 4);
        bi_sub(&pz_sub, pos_b, z);  // 뺄셈 수행

        bigint *nz_sub = NULL;
        bi_new(&nz_sub, 4);
        bi_sub(&nz_sub, neg_c, z);  // 뺄셈 수행

        bigint *zp_sub = NULL;
        bi_new(&zp_sub, 4);
        bi_sub(&zp_sub, z, pos_b);  // 뺄셈 수행

        bigint *zn_sub = NULL;
        bi_new(&zn_sub, 4);
        bi_sub(&zn_sub, z, neg_c);  // 뺄셈 수행

        //
        fprintf(file, "pos_a =");
        bi_fprint(file, pos_a);
        fprintf(file, "pos_b =");
        bi_fprint(file, pos_b);
        fprintf(file, "neg_c =");
        bi_fprint(file, neg_c);
        fprintf(file, "neg_d =");
        bi_fprint(file, neg_d);
        fprintf(file, "z =");
        bi_fprint(file, z);

        fprintf(file, "pp_sub = ");
        bi_fprint(file, pp_sub);
        fprintf(file, "nn_sub= ");
        bi_fprint(file, nn_sub);
        fprintf(file, "np_sub = ");
        bi_fprint(file, np_sub);
        fprintf(file, "pn_sub= ");
        bi_fprint(file, pn_sub);

        fprintf(file, "zp_sub = ");
        bi_fprint(file, zp_sub);
        fprintf(file, "zn_sub = ");
        bi_fprint(file, zn_sub);
        fprintf(file, "nz_sub = ");
        bi_fprint(file, nz_sub);
        fprintf(file, "pz_sub= ");
        bi_fprint(file, pz_sub);

        fprintf(file, "if (pos_a - pos_b != pp_sub):\n \t print(f\"{pos_a} - {pos_b} != {pp_sub}\") \n");
        fprintf(file, "if (neg_c - neg_d != nn_sub):\n \t print(f\"{neg_c} - {neg_d} != {nn_sub}\") \n");
        fprintf(file, "if (pos_a - neg_d != pn_sub):\n \t print(f\"{pos_a} - {neg_d} != {pn_sub}\") \n");
        fprintf(file, "if (neg_c - pos_b != np_sub):\n \t print(f\"{neg_c} - {pos_b} != {np_sub}\") \n");

        fprintf(file, "if (pos_b - z != pz_sub):\n \t print(f\"{pos_b} - {z} != {pz_sub}\") \n");
        fprintf(file, "if (neg_c - z != nz_sub):\n \t print(f\"{neg_c} - {z} != {nz_sub}\") \n");
        fprintf(file, "if (z - pos_b != zp_sub):\n \t print(f\"{z} - {pos_b} != {zp_sub}\") \n");
        fprintf(file, "if (z - neg_c != zn_sub):\n \t print(f\"{z} - {neg_c} != {zn_sub}\") \n");

        bi_delete(&pos_a);
        bi_delete(&pos_b);
        bi_delete(&neg_c);
        bi_delete(&neg_d);
        bi_delete(&z);

        bi_delete(&pp_sub);
        bi_delete(&nn_sub);
        bi_delete(&pn_sub);
        bi_delete(&np_sub);

        bi_delete(&pz_sub);
        bi_delete(&zn_sub);
        bi_delete(&nz_sub);
        bi_delete(&zp_sub);
    }

    fclose(file);
}
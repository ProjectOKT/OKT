#include <stdio.h>
#include <stdlib.h>


/************************
Use_Sage : Sample of Using Sage operating
************************/

int Use_Sage() {
    char buffer[500];   //크기 조절 필요
    FILE *fp;
    int result;

    //Sage 실행, 출력 가져오기
    fp = popen("sage -c 'print(2^128)'", "r");
    if (fp == NULL) {
        printf("NULL Error!\n");
        return 1;
    }

    // 명령어 결과를 읽어와서 저장
    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);

    //c에서의 자료형으로 나타낼 수 없으므로 문자열로 출력
    printf("SageMath에서 계산된 값: %s\n", buffer);

    return 0;
}

// int main(){
//     Use_Sage();
//     return 0;
// }
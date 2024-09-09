#include <stdio.h>

int main(){
    char str[4] = "Test";
    for(int i = 0; i < 4; i ++){
        printf("%s[%d]\n", str, i + 1);
    }
}

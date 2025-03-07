#include <stdio.h>

int main(void){
    int oriNum, num, ans;
    num = 0;
    ans = 1;

    printf("Enter a positive integer: ");
    scanf("%d", &num);
    oriNum = num;

    while (num > 0) {
        ans *= num;
        num --;
    }
    printf("%d! is %d\n", oriNum, ans);
}
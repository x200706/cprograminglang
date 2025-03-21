#include <stdio.h>
int gcd(int x, int y);

int main(void){
    int a;
    int b;
    printf("Enter two integer: ");
    scanf("%d%d",&a, &b);
    int ans = gcd(a, b);
    printf("Greatest common divisor of %d and %d is %d\n", a, b, ans);
}

int gcd(int x, int y) {
    int ans = 0;
    if (y == 0){
        return x;
    }
    else{
        return gcd(y, x % y);
    }
}
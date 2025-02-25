#include <stdio.h>

int main(void){
    int a; // 沒給值預設會隨機給個東西
    // C語言整數除整數會得到整數（截斷非四捨五入）
    
    // 一些安全性問題
    // scanf_s("%d", &a); // Windows好像才會發生https://blog.csdn.net/m0_62794055/article/details/123927964 scanf()改用scanf_s() 不然要修改前置處理

    printf("%s", "hello"); // 其實字串應該也要用格式輸出
    puts("會自己換行");
}
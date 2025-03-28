#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int arr[5] = {0};
    int mark[40] = {0};

    // 初始化隨機數種子
    srand(time(NULL));

    for (unsigned int i = 0; i < 5; ++i) {
        int num; // 定義在迴圈外，避免作用域問題
        int flag = 0;
        while (flag == 0) {
            num = 1 + (rand() % 39);
            if (mark[num] == 0) {
                flag = 1;
            }
        }
        arr[i] = num;
        mark[num] = 1;
    }

    for (unsigned int i = 0; i < 5; ++i) {
        printf("%d ", arr[i]);
    }
}


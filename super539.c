#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int arr[5] = {0};
    int mark[39] = {0};

    for (unsigned int i = 0; i < 5; ++i) {
        int num = 1 + (rand() % 39);
        int flag = 0;
        while (flag == 1) {
            num = 1 + (rand() % 39);
            if (mark[num] == 1) {
                flag = 1;
                break;
            }
        }
        arr[i] = num;
        mark[num] = 1;
    }

    for (unsigned int i = 0; i < 5; ++i) {
        printf("%d ", arr[i]);
    }
}
#include <stdio.h>

int bubble_sort_and_count_swaps(int n, int arr[]) {
    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交換元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
    return swaps;
}

int main() {
    int cases;
    scanf("%d", &cases); // 讀取測試案例數
    while (cases--) {
        int length;
        scanf("%d", &length); // 讀取火車節數
        int train[50]; // 假設最多50節車廂
        for (int i = 0; i < length; i++) {
            scanf("%d", &train[i]); // 讀取車廂順序
        }
        int swaps = bubble_sort_and_count_swaps(length, train);
        printf("Optimal train swapping takes %d swaps.\n", swaps);
    }
    return 0;
}
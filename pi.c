#include <stdio.h>
#include <math.h>

int main(void) {
	double deno = 1; // 分母
	double ans = 0;

	// 紀錄達成目標回合數
	int term314 = 0;
	int term3141 = 0;
	int term31415 = 0;
	int term314159 = 0;

	for (int term = 1; term <= 400000; term ++) {
		// 計算
		if (term % 2 != 0) { // 奇數圈是加
			ans += (double)4 / deno;
		} else { // 偶數圈是減
			ans -= (double)4 / deno;
		}
		
		// 判斷是否逼近目標
        if (term314 == 0 && fabs(ans - 3.14) <= 0.000001) {
            term314 = term;
        }
        if (term3141 == 0 && fabs(ans - 3.141) <= 0.000001) {
            term3141 = term;
        }
        if (term31415 == 0 && fabs(ans - 3.1415) <= 0.000001) {
            term31415 = term;
        }
        if (term314159 == 0 && fabs(ans - 3.14159) <= 0.000001) {
            term314159 = term;
        }
		deno += 2;
		printf("%d	%.6f\n", term, ans);
	}
	printf("The terms of this series before first get 3.14 is %d\n", term314);
	printf("The terms of this series before first get 3.141 is %d\n", term3141);
	printf("The terms of this series before first get 3.1415 is %d\n", term31415);
	printf("The terms of this series before first get 3.14159 is %d\n", term314159);
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int collectStudent(int n);
void showGroup(int group[3][50], int n);
int findStudentScore(int id);
int getUnRandomNum(int mark[100]);

int getUnRandomNum(int mark[100]) {
	int num; // 定義在迴圈外，避免作用域問題
	int flag = 0;
	while (flag == 0) {
		num = rand() % 100;
		if (mark[num] == 0) {
			flag = 1;
		}
	}
	mark[num] = 1;
	return num;
}

int collectStudent() {
	int students;
	printf("請輸入學生總人數：");
	scanf_s("%d", &students);
	return students;
}

int main(void)
{
	int mark1[100] = { 0 };
	int mark2[100] = { 0 };
	srand(time(NULL));
	printf("（不知道是不是scanf_s跟Windows CMD相關問題，可能要請多按幾次enter）\n");
	int students = collectStudent();

	while (students > 50 || students < 1) {
		printf("輸入錯誤！人數必須介於1 到 50 之間!\n請重新輸入：");
		students = collectStudent();
	}

	int data[50][2]; // 用來存放學生人數的陣列

	/*
	{{學號, 分數} * 50}
	*/

	// 技巧：不重複的學生跟不重複的分數化解要額外紀錄重複分數的問題
	printf("\n產生學生的資料：\n");
	for (int i = 0; i < students; i++) {
		data[i][0] = 16000 + getUnRandomNum(mark1); // 一個放學號
		data[i][1] = getUnRandomNum(mark2); // 一個放分數		
		printf("第 %d 位學生 － 學號：%d，成績：%d\n", i + 1, data[i][0], data[i][1]);
	}

	int group[3][50] = {0};
	/*
	核心問題：資料結構應該長甚麼樣子比較好？
	這樣設計看來分數要用反查的...
		{
		第0組表A	{學號arr * 50}, 不定長度陣列問題或是硬凹成字串 但要套用分隔符
		第1組表B	{學號arr * 50}, 可是拆出來會很麻煩...
		第2組表C	{學號arr * 50}, 畢竟這是C啊，乾脆每個都給50個位置
								反正學生最多才50個?
								啊沒有的學號就0 也是預設值
		}
	*/
	printf("\n分組結果：\n");
	for (int i = 0; i < students; i++) {
		// 先切割出尾數
		int tempTail;
		tempTail = data[i][0] - 16000; // 0~99
		// 看看個位數
		tempTail = tempTail % 10;
		// 根據尾數放進分組
		if ((tempTail >= 0) && (tempTail<= 3)) {
			group[0][i] = data[i][0];
		} else if ((tempTail >= 4) && (tempTail <= 6)) {
			group[1][i] = data[i][0];
		} else if ((tempTail >= 7) && (tempTail <= 9)) {
			group[2][i] = data[i][0];
		}
	}

	int aCount = 0;
	for (int i = 0; i < 50; i++) {
		if (group[0][i] != 0) {
			aCount += 1;
		}
	}
	printf("A 組人數：%d\n", aCount);

	int bCount = 0;
	for (int i = 0; i < 50; i++) {
		if (group[1][i] != 0) {
			bCount += 1;
		}
	}
	printf("B 組人數：%d\n", bCount);

	int cCount = 0;
	for (int i = 0; i < 50; i++) {
		if (group[2][i] != 0) {
			cCount += 1;
		}
	}
	printf("C 組人數：%d\n", cCount);

	// 全體平均分數
	int total = 0;
	for (int i = 0; i < students; i++) {
		total += data[i][1];
	}
	float mean = (float)total / (float)students;
	printf("\n全體平均成績：%.2f\n", mean);

	// 暴力法找高低分學生
	int maxOne[1][2] = { {0, 0} };
	int minOne[1][2] = { {0, -101} };
	/*
	{ {學號, 分數} } 順手用二維當dict用 仿照K、V結構
	*/
	// 先找最高
	for (int i = 0; i < students; i++) {
		int score = data[i][1];
		if (score > maxOne[0][1]) {
			maxOne[0][0] = data[i][0]; // 該生學號
			maxOne[0][1] = score;
		}
	}
	printf("\n最高成績學生 － 學號：%d，成績：%d\n", maxOne[0][0], maxOne[0][1]);

	// 把數字轉成負數找最低
	for (int i = 0; i < students; i++) {
		int sign_score = -data[i][1];
		if (sign_score > minOne[0][1]) {
			minOne[0][0] = data[i][0]; // 該生學號
			minOne[0][1] = sign_score;
		}
	}
	printf("最低成績學生 － 學號：%d，成績：%d\n", minOne[0][0], -minOne[0][1]);

	// 查詢模式 問題 要能重新查詢嗎？考卷上沒有
	// sizeof各組長度然後遍歷即可  不行!!因為我用了陣列預留法 size必為50

	int cho = 0;
	printf("\n請輸入查詢模式（1：A組，2：B組，3：C組）：");
	scanf_s("%d", &cho);
	switch (cho) {
		case 1:
			printf("A 組學生：\n");
			showGroup(group, data, 1);
			break;
		case 2:
			printf("B 組學生：\n");
			showGroup(group, data, 2);
			break;
		case 3:
			printf("C 組學生：\n");
			showGroup(group, data, 3);
			break;
		default:
			printf("無效的查詢模式！\n");
			break;
	}
	
}

void showGroup(int group[3][50], int data[50][2], int n) {
	int index = n - 1;
	if (index == 0) { // 遍歷A組學生
		for (int i = 0; i < 50; i++) {
			if (group[0][i] != 0) {
				printf("學號：%d，成績：%d\n", group[0][i], findStudentScore(data, group[0][i]));
			}
		}
	} else if (index == 1) { // 遍歷B組學生
		for (int i = 0; i < 50; i++) {
			if (group[1][i] != 0) {
				printf("學號：%d，成績：%d\n", group[1][i], findStudentScore(data, group[1][i]));
			}
		}
	} else if (index == 2) { // 遍歷C組學生
		for (int i = 0; i < 50; i++) {
			if (group[2][i] != 0) {
				printf("學號：%d，成績：%d\n", group[2][i], findStudentScore(data, group[2][i]));
			}
		}
	}
}

int findStudentScore(int data[50][2], int id) {
	int score = 0;
	for (int i = 0; i < 50; i++) {
		if (id == data[i][0]) {
			score = data[i][1];
		}
	}
	return score;
}
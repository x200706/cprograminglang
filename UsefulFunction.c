#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 知識點：在main方法以前定義的function不用宣告給編譯器知道
// 字串切割器
int split(char word[], char* tokens_out[]) { // 傳入的第二個參數是字元指標，可以直接添加字元
    int token_count = 0;
    char* token = strtok(word, " "); // 在這裡設置分割符

    while (token != NULL) {
        tokens_out[token_count++] = token;
        token = strtok(NULL, " ");
    }
    return token_count; // 回傳的是找到的token數量（因為回傳陣列不太方便）
}

int main() {
    // 使用字串切割器
	char word[101]; // 預計讀取100個字元
    // 讀取
	scanf("%100[^\n]", word); // 包含空白
    char* tokens[100]; // 預留100個位置
    int num_tokens = split(word, tokens);
    // 遍歷之
    for (int i = 0; i < num_tokens; i++) {
        printf("%s\n", tokens[i]);
    }

    //TODO 檔案處理相關
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    // char word[]; // 不可以這樣做

    // 差別：
    char word[100]; // 字元陣列
    char *tokens[50]; // 字串指標陣列
    
    puts("Enter a line of text:");
    scanf("%99[^\n]", word);
    printf("%s", word);

    // 使用strtok分詞
    int token_count = 0;
    char *token = strtok(word, " ");
    while (token != NULL) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    // 反向輸出
    printf("The tokens in reverse order are:\n");
    for (int i = token_count - 1; i >= 0; i--) {
        printf("%s", tokens[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}
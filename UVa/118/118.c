#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 51

int main() {
    int X, Y;
    bool scent[MAX_SIZE][MAX_SIZE] = {0};
    char directions[] = {'N', 'E', 'S', 'W'};
    int dx[] = {0, 1, 0, -1}; // 北、東、南、西的x變化
    int dy[] = {1, 0, -1, 0}; // 北、東、南、西的y變化
    char line[100], commands[100];
    int x, y, d;
    char dir[2];
    
    // 開啟輸入檔案
    FILE *file = fopen("1.in", "r");
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }

    // 讀取地圖尺寸
    if (fscanf(file, "%d %d", &X, &Y) != 2) {
        fclose(file);
        return 0;
    }
    fgetc(file); // 讀取換行符

    while (true) {
        if (fgets(line, sizeof(line), file) == NULL) break; // 讀取機器人初始位置和方向
        if (line[0] == '\n' || line[0] == '\0') continue; // 跳過空行

        if (sscanf(line, "%d %d %s", &x, &y, dir) != 3) continue;

        // 檢查方向是否合法
        int valid_dir = -1;
        for (int i = 0; i < 4; i++) {
            if (dir[0] == directions[i]) {
                valid_dir = i;
                break;
            }
        }

        // 如果方向無效或座標超出範圍，跳過指令
        if (valid_dir == -1 || x < 0 || x > X || y < 0 || y > Y) {
            fgets(line, sizeof(line), file);
            continue;
        }

        d = valid_dir;
        bool lost = false;

        // 讀取指令
        if (fgets(commands, sizeof(commands), file) == NULL) break;

        // 處理指令
        for (int i = 0; commands[i] != '\0' && commands[i] != '\n'; i++) {
            if (lost) break;
            if (commands[i] == 'L') {
                d = (d - 1 + 4) % 4; // 左轉
            } else if (commands[i] == 'R') {
                d = (d + 1) % 4; // 右轉
            } else if (commands[i] == 'F') { // 前進
                int nx = x + dx[d];
                int ny = y + dy[d];
                // 檢查是否超出邊界
                if (nx < 0 || nx > X || ny < 0 || ny > Y) {
                    if (!scent[x][y]) {
                        scent[x][y] = true;
                        lost = true;
                    }
                } else {
                    x = nx;
                    y = ny;
                }
            }
        }

        printf("%d %d %c", x, y, directions[d]);
        if (lost) {
            printf(" LOST\n");
        } else {
            printf("\n");
        }
    }

    fclose(file);
    return 0;
}
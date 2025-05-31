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

// 檔案開啟器
FILE* openFile(const char* fileName, const char* mode) { // rb+很實用
    FILE* filePoint = fopen(fileName, mode);
    if (filePoint == NULL) {
        printf("無法開啟檔案，請查照\n");
    }
    return filePoint;
}

struct structData {
//TODO 你的結構體屬性
    int id;
};

// 資料寫入器（增）
int writeData(FILE* filePoint, const struct structData* data) { // 後方Data要傳入struct structData blankStructData = {0, "", "", 0.0}; 或讀進來的也行
    if (filePoint == NULL || data == NULL) return -1;

    size_t itemWrite = fwrite(data, sizeof(struct structData), 1, filePoint);

    if (itemWrite == 1) {
        return 1;
    }
    else {
        printf("存檔失敗...\n");
        return -1;
    }
}

// 資料讀取器（查detail）
int readData(FILE* filePoint, struct structData* data) {
    if (filePoint == NULL || data == NULL) return -1;
    clearerr(filePoint);
    size_t itemRead = fread(data, sizeof(struct structData), 1, filePoint);
    if (itemRead == 1) {
        return 1;
    }
    else if (feof(filePoint)) {
        return 0; // EOF
    }
    else {
        printf("讀取記錄失敗...\n");
        return -1;
    }
}

// 資料查找器（同時，會移動指針）（查target）
int seekData(FILE* filePoint, int id) {
    if (filePoint == NULL || id <= 0) return -1;
    if (fseek(filePoint, (long)(id - 1) * sizeof(struct structData), SEEK_SET) != 0) {
        printf("查詢指針移動失敗...\n");
        return -1;
    }
    return 0;
}

bool updateDataById(FILE* filePoint, int idToUpdate, const struct structData* dataForUpdate) {
    // 參數檢查
    if (filePoint == NULL) { printf("更新失敗：檔案指標為空\n"); return false; }
    if (dataForUpdate == NULL) { printf("沒有傳入更新用的資料\n"); return false; }
    if (dataForUpdate->id != idToUpdate) { printf("更新資料ID與結構體內部ID不符\n"); return false; }
    if (idToUpdate <= 0) { printf("更新失敗：無效的目標ID\n"); return false; }

    struct structData recordOnFile = { 0 };
    long offset = (long)(idToUpdate - 1) * sizeof(struct structData);

    clearerr(filePoint);

    if (fseek(filePoint, offset, SEEK_SET) != 0) {
        printf("移動失敗\n");
        return false;
    }

    // 2. 讀取記錄
    if (fread(&recordOnFile, sizeof(struct structData), 1, filePoint) != 1) {
        if (feof(filePoint)) {
            printf("EOF\n");
        }
        else {
            printf("讀取記錄失敗...\n");
        }
        return false;
    }

    if (recordOnFile.id == 0) {
        printf("原始資料有誤\n");
        return false;
    }
    if (recordOnFile.id != idToUpdate) {
        printf("檔案損毀\n");
        return false;
    }

    if (fseek(filePoint, offset, SEEK_SET) != 0) {
        printf("移動失敗\n");
        return false;
    }

    if (fwrite(dataForUpdate, sizeof(struct structData), 1, filePoint) != 1) {
        printf("存檔失敗...\n");
        return false;
    }
    return true;
}

bool deleteDataById(FILE* filePoint, unsigned int idToDelete) {
    // 參數檢查
    if (filePoint == NULL) { printf("檔案指標為空\n"); return false; }
    if (idToDelete == 0) { printf("無效的記錄ID\n"); return false; }

    struct structData recordOnFile;
    struct structData blankRecord = { 0 };
    long offset = (long)(idToDelete - 1) * sizeof(struct structData);

    clearerr(filePoint);

    if (fseek(filePoint, offset, SEEK_SET) != 0) {
        printf("移動失敗\n");
        return false;
    }

    if (fread(&recordOnFile, sizeof(struct structData), 1, filePoint) != 1) {
        if (feof(filePoint)) {
            printf("EOF\n");
        }
        else {
            printf("讀取記錄失敗...\n");
        }
        return false;
    }

    if (recordOnFile.id == 0) {
        printf("紀錄早已為空\n");
        return true; // 認為刪除一個已空的記錄是成功的
    }
    if (recordOnFile.id != idToDelete) {
        printf("已有紀錄ID與欲刪除記錄不同");
        return false;
    }

    if (fseek(filePoint, offset, SEEK_SET) != 0) {
        printf("移動失敗\n");
        return false;
    }

    if (fwrite(&blankRecord, sizeof(struct structData), 1, filePoint) != 1) {
        printf("刪除失敗\n");
        return false;
    }

    return true;
}

// 初始化檔案
bool initFile(const char* fileName, int numRecords) {
    FILE* filePoint = openFile(fileName, "wb");
    if (filePoint == NULL) return false;
    struct structData blankRecord = { 0 };
    for (int i = 0; i < numRecords; ++i) {
        if (writeData(filePoint, &blankRecord) != 1) {
            fclose(filePoint);
            return false;
        }
    }
    fclose(filePoint);
    return true;
}

// 添加新資料 (尋找空位)
bool addNewData(FILE* filePoint, const struct structData* newData) {
    if (filePoint == NULL || newData == NULL || newData->id == 0) return false;
    struct structData tempRecord;
    int currentPositionId = 1;
    rewind(filePoint);
    while (readData(filePoint, &tempRecord) == 1) {
        if (tempRecord.id == 0) {
            if (seekData(filePoint, currentPositionId) != 0) return false;
            return writeData(filePoint, newData) == 1;
        }
        currentPositionId++;
    }
    printf("添加新資料失敗");
    return false;
}

// 顯示所有有效資料
void displayAllData(FILE* filePoint) {
    if (filePoint == NULL) return;
    rewind(filePoint);
    struct structData record;
    int count = 0;
    printf("檔案內容：\n");
    while (readData(filePoint, &record) == 1) {
        if (record.id != 0) {
            printf("ID: %d\n", record.id);
            count++;
        }
    }
    if (count == 0) printf(" (空)\n");
}

// 資料追加器（總是在檔案末尾添加）
bool appendNewData(FILE* filePoint, const struct structData* newData) {
    if (filePoint == NULL || newData == NULL || newData->id == 0) {
        printf("追加資料失敗\n");
        return false;
    }
    // 直接使用 fseek
    if (fseek(filePoint, 0, SEEK_END) != 0) {
        printf("移動失敗\n");
        return false;
    }
    if (writeData(filePoint, newData) != 1) {
        return false;
    }
    return true;
}

// test檔案處理相關func
void testFileFunc() {
    const char* dataFileName = "mySimpleData.dat";
    FILE* fp = NULL;

    fp = openFile(dataFileName, "rb+");
    if (fp == NULL) {
        if (!initFile(dataFileName, 5)) {
            printf("初始化失敗，程式終止。\n");
            return;
        }
        fp = openFile(dataFileName, "rb+");
        if (fp == NULL) {
            printf("重新開啟失敗，程式終止。\n");
            return;
        }
    }

    printf("添加操作\n");
    struct structData r1 = { 1 };
    struct structData r2 = { 2 };
    struct structData r3 = { 3 };
    if (addNewData(fp, &r1)) printf("添加 ID 1 成功。\n"); else printf("添加 ID 1 失敗。\n");
    if (addNewData(fp, &r2)) printf("添加 ID 2 成功。\n"); else printf("添加 ID 2 失敗。\n");
    if (addNewData(fp, &r3)) printf("添加 ID 3 成功。\n"); else printf("添加 ID 3 失敗。\n");
    displayAllData(fp);

    printf("更新操作\n");
    struct structData rUpdate = { 2 };
    if (updateDataById(fp, 2, &rUpdate)) {
        printf("更新 ID 2 成功。\n");
    }
    else {
        printf("更新 ID 2 失敗。\n");
    }
    displayAllData(fp);

    printf("刪除操作\n");
    if (deleteDataById(fp, 1)) {
        printf("刪除 ID 1 成功。\n");
    }
    else {
        printf("刪除 ID 1 失敗。\n");
    }
    displayAllData(fp);

    printf("再次添加操作 (到空位)\n");
    struct structData r4 = { 4 };
    if (addNewData(fp, &r4)) printf("添加 ID 4 成功。\n"); else printf("添加 ID 4 失敗。\n");
    displayAllData(fp);

    printf("追加操作 (到檔案尾端)\n");
    struct structData r5 = { 5 };
    if (appendNewData(fp, &r5)) printf("追加 ID 5 成功。\n"); else printf("追加 ID 5 失敗。\n");
    displayAllData(fp);

    if (fclose(fp) == EOF) {
        printf("關檔失敗\n");
    }
    else {
        printf("\n檔案已關閉。\n");
    }
}

int main() {
    /*
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
    */
    // 檔案處理相關
    testFileFunc();
}
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*-----------函數區-----------*/
// 字串切割器
int split(char word[], char* tokens_out[]) {
    int token_count = 0;
    char *token = strtok(word, ","); // 在這裡設置分割符為,

    while (token != NULL) {
        tokens_out[token_count++] = token;
        token = strtok(NULL, ","); // 在這裡設置分割符為,
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
    // 商品結構體屬性
    int id;
    int price;
    int type; //HINT 先不走枚舉全靠硬A
    char *name; // 字串 可直接name = "apple"
    int inStock; // 0表不在庫 1表在庫
    int onSale; // 0表不特價 1表特價
    //TODO 用逗號(CSV)儲存資料，讀回來用我寫的split()來切!!<-不過做不來不勉強...
};
typedef struct structData Good;

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
    FILE* filePoint = openFile(fileName, "w");
    if (filePoint == NULL) return false;
    struct structData blankRecord = { 0, 0, 0, "none", 0, 0};
    /*
    // 商品結構體屬性
    int id;
    int price;
    int type; //HINT 先不走枚舉全靠硬A
    char *name; // 字串 可直接name = "apple"
    int inStock; // 0表不在庫 1表在庫
    int onSale; // 0表不特價 1表特價
    */
    for (int i = 0; i < numRecords; ++i) {
        if (writeData(filePoint, &blankRecord) != 1) {
            fclose(filePoint);
            return false;
        }
    }
    fclose(filePoint);
    return true;
}

/*
// 順序會亂掉故棄用
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
*/

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

/*-----------主程式-----------*/
// 下稱產品為Goods

/*HINT 第一個功能的考驗是怎麼存 我可以存在tempFile 陣列 很多地方
哪個比較好？<-內容物是結構體的陣列*/
// 因應選單系統全得是void

// 第一題完成!
void addGoods(Good goods[50]) {
    // 商品結構體屬性
    int id;
    int price;
    int type; //HINT 先不走枚舉全靠硬A
    char name[55]; // 字串 可直接name = "apple"
    /*
    int inStock; // 0表不在庫 1表在庫
    int onSale; // 0表不特價 1表特價
    */
    printf("\n請輸入商品名稱：");
    scanf("%s", &name);
    
    printf("\n請輸入商品編號（0-49）：");
    scanf("%d", &id);
    while (id > 49 || id < 0) { // 第六題完成，其他限制詳參程式
        printf("\n無效的商品編號!!\n");
        printf("\n請重新輸入商品編號：（0-49）");
        scanf("%d", &id);
    }

    printf("\n請輸入商品類型（0是食物，1是電子，2是衣服）：");
    scanf("%d", &type);

    printf("\n請輸入商品價格：");
    scanf("%d", &price);
    
    struct structData tempGood = { id, price, type, name, 0, 0 }; //HINT 其實屬性這樣亂序很難看
    goods[id] = tempGood;
    printf("\n商品添加成功！！\n"); //TODO 其實這邊只要暫存結構體在記憶體

    // return goodsCount; // 回傳一個新的goodsCount
    // 別這樣做 直接修改指標指的東西
}

// 第二題完成!
void displayGoods(Good goods[50]) {
    printf("將為您依序顯示商品：\n");
    for (size_t i = 0; i < 50; i++) {
        if (goods[i].id >= 0 && goods[i].id <=49) {
            // 轉換器
            char* typeName = "";
            if (goods[i].type == 0) {
                typeName = "食物";
            }
            else if (goods[i].type == 1) {
                typeName = "電子";
            }
            else if (goods[i].type == 2) {
                typeName = "衣服";
            }

            char* inStockStr = "";
            if (goods[i].inStock == 0) {
                inStockStr = "no";
            }
            else {
                inStockStr = "yes";
            }

            char* onSaleStr = "";
            if (goods[i].inStock == 0) {
                onSaleStr = "no";
            }
            else {
                onSaleStr = "yes";
            }

            printf("商品編號ID：%d，商品名稱：%s，類型：%s，價格：%d，在庫：%s，促銷：%s\n",
                goods[i].id,
                goods[i].name,
                typeName,
                goods[i].price,
                inStockStr,
                onSaleStr
            );
        }
    }
    /*
    // 商品結構體屬性
    int id;
    int price;
    int type; //HINT 先不走枚舉全靠硬A
    char *name; // 字串 可直接name = "apple"
    int inStock; // 0表不在庫 1表在庫
    int onSale; // 0表不特價 1表特價
    */
}

// 第三題完成!
void saveGoods(Good goods[50]) {
    //HINT 開檔 寫檔 存檔 關檔
    FILE* cfPtr;

    if ((cfPtr = fopen("items.txt", "w")) == NULL) {
        puts("建立檔案失敗...");
    }
    else {
        for (size_t i = 0; i < 50; i++) {
            if (goods[i].id >= 0 && goods[i].id <= 49) {
                fprintf(cfPtr, "%d,%s,%d,%d,%d,%d\n",
                    goods[i].id,
                    goods[i].name,
                    goods[i].type,
                    goods[i].price,
                    goods[i].inStock,
                    goods[i].onSale);
            }
        }
    }
    fclose(cfPtr);
    printf("商品儲存成功！！\n");
}

// 第四題
void loadGoods() { // 看看要傳啥
    printf("將為您依序載入商品資料：\n");

    FILE* cfPtr;

    if ((cfPtr = fopen("items.txt", "r")) == NULL) {
        puts("讀檔失敗！！");
    } else { 
        // 商品結構體屬性
        int id;
        int price;
        int type; //HINT 先不走枚舉全靠硬A
        char name[55]; // 字串 可直接name = "apple"
        int inStock; // 0表不在庫 1表在庫
        int onSale; // 0表不特價 1表特價

        char lineStr[255]; // 先假設csv一行至多255字元吧        

        while (!feof(cfPtr)) {
            fscanf(cfPtr, "%s", &lineStr);
            printf("%s\n", lineStr);
        }

        printf("第四題沒寫完整 沒能依照指定格式印出 還會重複印QQ\n");
        
        fclose(cfPtr); 
    }
}

int exitThisSystem() { // 看看要傳啥
    printf("退出系統...\n");
    exit();
    return 0; // 無異常退出~
}

int main(void)
{                     
    //HINT 檔案相關不要用開檔小幫手，重新寫，不然程式實在是太複雜了......

    // 暫存結構體：離開程式會清空
    Good goods[50];
    /*廢案 改用使用者輸入的ID
    int goodsCount = 0; // 0~49 紀錄使用槽位
    int* goodsCountPtr = &goodsCount;*/

    printf("老師您好，可能是Windows exe檔的特性，每個選項有時候要按Enter第二次程式才會開始運行\n");
    
    // void (*f[5])(int) = { addGoods, DisplayGoods, saveGoods, loadGoods, exitThisSystem };
    // HINT 為了好傳參數還是改回switch case
    printf("=========== 庫存系統選單 ===========\n");
    printf("1. 新增項目\n");
    printf("2. 顯示所有項目\n");
    printf("3. 儲存項目\n");
    printf("4. 載入項目\n");
    printf("5. 離開\n");
    printf("請輸入選擇（1-5）：");
    size_t choice; // variable to hold user's choice
    scanf("%u", &choice);
    choice -= 1; //HINT 陣列陷阱
    // process user's choice
    while (choice >= 0 && choice < 4) {                       
        // (*f[choice])(choice);
        switch (choice) {
        case 0:
            addGoods(goods);
            break;
        case 1:
            displayGoods(goods);
            break;
        case 2:
            saveGoods(goods);
            break;
        case 3:
            loadGoods(); 
            break;
        case 4:
            exitThisSystem(); // 第五題完成，除了沒用enum跟位元處理
            break;
        default:
            puts("無效選項！！");
            break;
        }

        printf("請輸入選擇（1-5）：");
        scanf("%u", &choice);
        choice -= 1; //HINT 陣列陷阱
    }
}
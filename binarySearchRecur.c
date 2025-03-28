// 改編自課本的Fig. 6.19: fig06_19.c
// Binary search of a sorted array.
#include <stdio.h>
#define SIZE 15

// function prototypes
size_t binarySearch(const int b[], int searchKey, size_t low, size_t high);
size_t binarySearchOrigi(const int b[], int searchKey, size_t low, size_t high);
void printHeader(void);
void printRow(const int b[], size_t low, size_t mid, size_t high);

// function main begins program execution
int main(void)
{
    int a[SIZE]; // create array a

    // create data
    for (size_t i = 0; i < SIZE; ++i) {
        a[i] = 2 * i;
    }

    printf("%s", "Enter a number between 0 and 28: ");
    int key; // value to locate in array a
    scanf_s("%d", &key);

    printHeader();

    // search for key in array a
    size_t result = binarySearch(a, key, 0, SIZE - 1);

    // display results
    if (result != -1) {
        printf("\n%d found at index %d\n", key, result);
    }
    else {
        printf("\n%d not found\n", key);
    }
}

// function to perform binary search of an array
size_t binarySearch(const int b[], int searchKey, size_t low, size_t high)
{
    // 基本情況：如果 low > high，代表沒找到，返回 -1
    if (low > high) {
        return -1;
    }

    // 計算中間位置
    size_t middle = (low + high) / 2;

    // 可選：顯示當前搜尋的子陣列
    printRow(b, low, middle, high);

    // 如果找到目標值，返回中間位置
    if (searchKey == b[middle]) {
        return middle;
    }
    // 如果搜尋值小於中間值，遞迴搜尋左半邊
    else if (searchKey < b[middle]) {
        return binarySearch(b, searchKey, low, middle - 1);
    }
    // 如果搜尋值大於中間值，遞迴搜尋右半邊
    else {
        return binarySearch(b, searchKey, middle + 1, high);
    }
}

// Print a header for the output
void printHeader(void)
{
    puts("\nSubscripts:");

    // output column head
    for (unsigned int i = 0; i < SIZE; ++i) {
        printf("%3u ", i);
    }

    puts(""); // start new line of output

    // output line of - characters
    for (unsigned int i = 1; i <= 4 * SIZE; ++i) {
        printf("%s", "-");
    }

    puts(""); // start new line of output
}

// Print one row of output showing the current
// part of the array being processed.
void printRow(const int b[], size_t low, size_t mid, size_t high)
{
    // loop through entire array
    for (size_t i = 0; i < SIZE; ++i) {

        // display spaces if outside current subarray range
        if (i < low || i > high) {
            printf("%s", "    ");
        }
        else if (i == mid) { // display middle element
            printf("%3d*", b[i]); // mark middle value
        }
        else { // display other elements in subarray
            printf("%3d ", b[i]);
        }
    }

    puts(""); // start new line of output
}

size_t binarySearchOrigi(const int b[], int searchKey, size_t low, size_t high)
{
    // loop until low index is greater than high index
    while (low <= high) {

        // determine middle element of subarray being searched
        size_t middle = (low + high) / 2;

        // display subarray used in this loop iteration
        printRow(b, low, middle, high);

        // if searchKey matched middle element, return middle
        if (searchKey == b[middle]) {
            return middle;
        }

        // if searchKey is less than middle element, set new high
        else if (searchKey < b[middle]) {
            high = middle - 1; // search low end of array      
        }

        // if searchKey is greater than middle element, set new low
        else {
            low = middle + 1; // search high end of array        
        }
    } // end while

    return -1; // searchKey not found
}

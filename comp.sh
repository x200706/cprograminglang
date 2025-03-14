#!/bin/bash

# 檢查是否有提供參數
if [ -z "$1" ]; then
  echo "請提供一個 .c 檔案作為參數"
  exit 1
fi

# 獲取檔案名稱（不包含副檔名）
filename=$(basename "$1" .c)

# 編譯 .c 檔案成 .out
gcc -o "$filename.out" "$1"

# 檢查編譯是否成功
if [ $? -eq 0 ]; then
  echo "編譯成功，輸出檔案為 $filename.out"
else
  echo "編譯失敗"
fi
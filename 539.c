#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
   // srand(time()); // 用時間當作亂數種子的方法
   for (unsigned int i = 1; i <= 5; ++i) {
      printf("%10d", 1 + (rand() % 39));
      if (i % 5 == 0) {
         puts("");
      } 
   } 
} 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char areaNum[6];
    char phoneNum[10];
    puts("Enter a phone number in the form (555) 555-5555:");
    scanf("%5s", areaNum);
    scanf("%9s", phoneNum);
    
    puts("");

    char *area;
    int areaCode;

    area = strtok(areaNum, "()");
    while( area != NULL ) {
        // NULL是我不要剩餘字串地址（要的話就要傳的指針進去）；10表十進位
        areaCode = strtol(area, NULL, 10);
        printf("The integer area code is %d\n", areaCode);
        area = strtok(NULL, "()");
    }

    char *part1 = strtok(phoneNum, "-");
    char *part2 = strtok(NULL, "-");
    if (part1 && part2) {
        strcat(part1, part2);
        long lPhoneNum = strtol(part1, NULL, 10);
        printf("The long integer phone number is %ld\n", lPhoneNum);
    }
}
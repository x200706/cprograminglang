#include <stdio.h>

int main(void){
    int height, weight, bmi;
    // ex: 138磅 63英吋
    printf("Please enter your height (in inches): ");
    scanf("%d", &height); 
    printf("Please enter your weight (in pounds): ");   
    scanf("%d", &weight);

    bmi = (weight * 703) / (height * height);

    printf("Your BMI is %d\n\n", bmi); 
    puts("BMI VALUES"); 
    puts("Underweight:  less than 18.5"); 
    puts("Normal:       between 18.5 and 24.9"); 
    puts("Overweight:   between 25 and 29.9"); 
    puts("Obese:        30 or greater"); 
}
   


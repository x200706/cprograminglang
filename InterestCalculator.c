#include <stdio.h>

int main(void){
    float principal, interest, rate;
    int days;
    
    printf("Enter loan principal (-1 to end): ");
    scanf("%f", &principal);

    while ((int)principal != -1) {    
        printf("Enter interest rate: ");
        scanf("%f", &rate);

        printf("Enter term of the loan in days: ");
        scanf("%d", &days);


        interest = (float)principal * rate * days / 365;
        printf("The interest charge is $%.2f\n", interest);
        principal = -1;
    }


}
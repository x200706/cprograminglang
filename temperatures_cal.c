#include <stdio.h>

int main(void) {
	puts("Conversion of temperature from Celsius to Fabrenheut");
	puts("Celsius Fabrenheut");
	float newTe;
	for (int te = 30; te <= 50;te ++) {
		newTe = 9 * (float)te / 5 + 32;
		printf("%d	%.2f\n", te, newTe);
	}
}
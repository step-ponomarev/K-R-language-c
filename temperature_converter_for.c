#include "stdio.h"

#define LOWER = 0
#define UPPER = 300
#define STEP = 20

float convertFahrenheitToCelsius(int);

int main() {
    for (int fahr = LOWER; fahr <= UPPER; fahr += STEP) {
        printf("%3d\t\t%6.1f\n", fahr, convertFahrenheitToCelsiu(fahr));
    }
    
    return 0;
}

float convertFahrenheitToCelsius(int farth) {
    return (5.0 / 9.0) * (farth - 32.0);
}
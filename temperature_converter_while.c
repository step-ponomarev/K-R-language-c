#include "stdio.h"

/*
    Вывод для температур по Фаренгейту и Цельсию 
    для farth от 0 до 300
*/

float convertFahrenheitToCelsius(int);
float convertCelsiusToFahrenheit(int);

int main() {
    float farth, celsium;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahrenheit\tCelsius\n");
    while (lower <= upper) {
        farth = lower;
        celsium = convertFahrenheitToCelsius(farth);
        printf("%3.0f\t\t%6.1f\n", farth, celsium);
        lower += step;
    }

    printf("Celsius\tFahrenheit\n");
    lower = 0;
    while (lower <= upper) {
        celsium = lower;
        farth = convertCelsiusToFahrenheit(celsium);
        printf("%3.0f\t\t%6.1f\n", celsium, farth);
        lower += step;
    }

    return 0;
}

float convertFahrenheitToCelsius(int farth) {
    return (5.0 / 9.0) * (farth - 32.0);
}

float convertCelsiusToFahrenheit(int celsium) {
    return (9.0 / 5.0) * (celsium) + 32.0;
}
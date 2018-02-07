#include <stdio.h>

/*Modify the temperature conversion program to print a heading above the table*/

int main()
{
    double fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    printf("\nThere is the table by conversion from Fahrenheit to Celsius\n"
                   "Fahrenheit Celsius\n");

    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32);
        printf("%-10.0f %-6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}
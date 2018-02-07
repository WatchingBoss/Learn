#include <stdio.h>

/*Write a program to print the corresponding Celsius to Fahrenheit table.*/

int main()
{
    double fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;

    printf("\nThere is the table by conversion Celsius to Fahrenheit\n"
                   "Celsius Fahrenheit\n");

    while (celsius <= upper) {
        fahr = celsius * (9.0 / 5.0) + 32;
        printf("%-7.0f %-8.0f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;	
}

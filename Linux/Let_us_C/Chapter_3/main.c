#include <stdio.h>

/* Program to determine whether a number is prime or not*/
void primeNumber()
{
    int number, i;
    puts("Prompt a number");
    scanf("%d", &number);
    i = 2;
    while (i <= number - 1)
    {
        if (number % i == 0)
        {
            puts("Not a primer number");
            break;
        }
        i++;
    }
    if (i ==  number)
        puts("Primer number");
}

int main()
{
    return 0;
}
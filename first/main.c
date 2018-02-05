#include <stdio.h>

int fact(int x)
{
    if (x == 1) return 1;
    return x * fact(x - 1);
}

int main() {
    int num;
    puts("Enter your number: ");
    scanf("%i", &num);
    printf("The factorial of %i: %i\n", num,  fact(num));
    return 0;
}
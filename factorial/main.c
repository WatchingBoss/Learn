#include <stdio.h>

int fact(int x){
    if (x == 1) return 1;
    printf("%i\n", x);
    return x * fact (x - 1);
}

int main() {
    int num;
    puts("Enter number for computing factorial");
    scanf("%i", &num);
    printf("Factorial of %i is: %i\n", num, fact(num));
    return 0;
}
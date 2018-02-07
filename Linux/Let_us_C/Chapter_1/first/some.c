/* For something */
/* Author Egor Data: 06/02/2018*/

#include <stdio.h>
#include <math.h>
#include "func_for_io.h"

/* using math.h for pow
 * remember: you need change CMakeList.txt for add library*/
double power(double number, double powering)
{
    double x;
    x = pow (number, powering);
    return x;
}

// simple func for check operators' proprietary
float example1_1()
{
    float i, i2;
    i = 2 * 3 / 4 + 4 / 4 + 8 - 2 + 5 / 8;
    i2 = (((((2 * 3) / 4) + (4 / 4)) + 8) - 2) + (5 / 8);
    if (i == i2)
        puts("You are right");
    else
        puts("You are wrong");
    printf("i  is %.1f\ni2 is %.1f\n\n", i, i2);
    return 1;
}

int main()
{
    char answer;
    answer = get_char("Prompt you answer Y/N: ");
    if (answer == 'y' || answer == 'Y')
        printf("Your answer yes\n");
    else if (answer == 'n' || answer == 'N')
        printf("Your answer is no\n");
    else
        printf("Fail answer");


/*//    get_string is function from func_for_io.h file, which invites put name
    char *word;
    word = get_string("Enter name: ");
    printf("Hello, %s\n\n", word);

//    get_int is function from func_for_io.h too, which invites put integer
    int number;
    number = get_int("Enter integer: ");
    printf("It\'s works, your integer is %i\n\n", number);

//    invited put float
    float num;
    num = get_float("Enter real: ");
    printf("It\'s work too, your real is %.2f\n\n", num);

    example1_1();

    printf ("Result: %.2f\n\n", power (5, 4)); // using function power


    *//* addition ASCII values of characters*//*
    char a, b;
    int z;
    int a1, b1;

    a = 'Y';
    b = 's';
    z = a + b;

    a1 = a;
    b1 = b;

    printf("Result: %d\n", z);
    printf("Because value of %c is %d and %c is %d\n", a, a1, b, b1);*/

    return 0;
}

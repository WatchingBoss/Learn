/* Example for Artem.
 * I need your help, friend:) */

#include <stdio.h>

void notWorkEx()
{
    char someS[80];
    puts("Do you want to continue? Y/N");
    if (fgetc(stdin) == 'y' || fgetc(stdin) == 'Y')
    {
        puts("Prompt some sentence");
        fgets(someS, sizeof(someS), stdin);
        printf("fgets does not work :((\n%s", someS);
    }
}

void wordEx()
{
    char someS[80];
    puts("Do you want to continue? Y/N");
    if (fgetc(stdin) == 'y' || fgetc(stdin) == 'Y')
    {
        puts("Prompt some sentence");

        fgetc(stdin); // It fixes problem

        fgets(someS, sizeof(someS), stdin);
        printf("Everything is OK :))\n%s", someS);
    }
}

int main()
{
    notWorkEx();
    puts("");
    wordEx();
    puts("");

    return 0;
}
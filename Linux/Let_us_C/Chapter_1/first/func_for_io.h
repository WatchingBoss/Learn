//
// Created by ubu on 2/6/18.
//

#ifndef FIRST_FUNC_FOR_IO_H
#define FIRST_FUNC_FOR_IO_H

char something[20];
int someNumber;
float someReal;
char character;

char get_char(char *some)
{
    printf("%s\n", some);
    scanf("%c", &character);
    return character;
}

char *get_string(char *some)
{
    printf("%s\n", some);
    scanf("%s", something);
    return something;
}

int get_int(char *some)
{
    printf("%s\n", some);
    scanf("%i", &someNumber);
    return someNumber;
}

float get_float(char *some)
{
    printf("%s\n", some);
    scanf("%f", &someReal);
    return someReal;
}

#endif //FIRST_FUNC_FOR_IO_H


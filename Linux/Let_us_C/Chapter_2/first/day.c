#include <stdio.h>

void weekDayName(int day, int month, int year)
{
    char *dayWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday",
                       "Friday", "Saturday", "Sunday"};
    int i = (day
             + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5)
             + (365 * (year + 4800 - ((14 - month) / 12)))
             + ((year + 4800 - ((14 - month) / 12)) / 4)
             - ((year + 4800 - ((14 - month) / 12)) / 100)
             + ((year + 4800 - ((14 - month) / 12)) / 400) - 32045) % 7;
    printf("It is %s\n", dayWeek[i]);
}

int main()
{
    int day, month, year;
    printf("Prompt data in format (DD MM YYYY)");
    scanf("%d %d %d", &day, &month, &year);
    weekDayName(day, month, year);
    return 0;
}
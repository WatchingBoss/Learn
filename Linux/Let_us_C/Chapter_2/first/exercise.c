/* Exercise for chapter 2*/
#include <stdio.h>

/* C. Attempt the following*/
/* Exercise a
 * If cost price and silling price of an item is input through the
 * keyboard, write a program to determine whether the seller has made
 * profit or incurred loss. Also determine how much profit he made
 * or loss he incurred.*/
void CA(int cost, int sell)
{
    if (cost < sell)
        printf("Your incurred loss is %d\n", sell - cost);
    else if (cost > sell)
        printf("Your profit is %d\n", cost - sell);
    else
        puts("Cost is equal to sell");
}

/* Exercise b
 * ANy integer is input through the keyboard. Write a program to find
 * out whether it is an odd number or even number.*/
void CB(int number)
{
    if (number % 2 == 1)
        printf("%d is odd number\n", number);
    else
        printf("%d is even number\n", number);
}

/* Exercise c
 * Any year is input through the keyboard. Write a program to determine
 * whether the year is a leap year or not.*/
void CC(int year)
{
    if (year % 400 == 0)
        printf("%d is leap year. It has 366 days\n", year);
    else if (year % 100 == 0)
        printf("%d is not leap year. It has 365 days\n", year);
    else if (year % 4 == 0)
        printf("%d is leap year. It has 366 days\n", year);
    else
        printf("%d is not leap year. It has 365 days\n", year);
}

/* Exercise d
 * According to hte Gregorian calendar, it was Monday on the date
 * 01/01/1900. If any year is input through the keyboard write a program
 * to find out what is the day on 1th January of this year*/
void CD(int year)
{
    int i;
    char *dayWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"};
    i = (1 + 306 + (365 * (year + 4800 - 13 / 12)) +
            ((year + 4800 - 13 / 12) / 4) -
            ((year + 4800 - 13 / 12) / 100) +
            ((year + 4800 - 13 / 12) / 400) - 32045) % 7;
    printf("%d\n", i);
    printf("%s\n", dayWeek[i]);
}

/* const char *wd(int year, int month, int day) {
  using C99 compound literals in a single line: notice the splicing
return ((const char *[])                                         \
          {"Monday", "Tuesday", "Wednesday",                       \
           "Thursday", "Friday", "Saturday", "Sunday"})[           \
      (                                                            \
          day                                                      \
        + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5) \
        + (365 * (year + 4800 - ((14 - month) / 12)))              \
        + ((year + 4800 - ((14 - month) / 12)) / 4)                \
        - ((year + 4800 - ((14 - month) / 12)) / 100)              \
        + ((year + 4800 - ((14 - month) / 12)) / 400)              \
        - 32045                                                    \
      ) % 7];
}*/

/* const char *wd(int year, int month, int day) {
  static const char *weekdayname[] = {"Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  size_t JND =                                                     \
          day                                                      \
        + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5) \
        + (365 * (year + 4800 - ((14 - month) / 12)))              \
        + ((year + 4800 - ((14 - month) / 12)) / 4)                \
        - ((year + 4800 - ((14 - month) / 12)) / 100)              \
        + ((year + 4800 - ((14 - month) / 12)) / 400)              \
        - 32045;
  return weekdayname[JND % 7];
}*/

int main()
{
    CD(2015);
    return 0;
}
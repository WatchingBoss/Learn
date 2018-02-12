#include <stdio.h>

/* Example 2.1
 * While purchasing certain items, a discount of 10% is offered if the
 * quantity purchased is more than 1000. If quantity and price per item are
 * input through the keyboard, write a program to calculate the total expenses.*/
void total(int quantity, int priceItem)
{
    int condition = 1000;
    float dis = 0;
    float totalExpenses;
    if (quantity >= condition)
    {
        dis = 0.1f;
        puts("You have discount 10%");
    }
    totalExpenses = quantity * (priceItem - dis * priceItem);
    printf("The total is %.0f\n", totalExpenses);
}

/* Example 2.2
 * The current year and the year in which the employee joined the organization
 * are entered through the keyboard. if the number of years for which
 * the employee has served the organization is greater than  then a bonus
 * of Rs. 2500/- is given to the employee. If the tears of service are not
 * greater than 3, then the program should do nothing.*/
void bonusForEmployee(int currentYear, int joinedYear)
{
    int condition = 3;
    int bonus, yearOfServer;
    yearOfServer = currentYear - joinedYear;
    if (yearOfServer < condition)
        puts("Nothing!");
    else if (yearOfServer >= condition)
    {
        bonus = 2500;
        printf("Your have a bonus %d\n", bonus);
    }
}

int main() {

    
    return 0;
}
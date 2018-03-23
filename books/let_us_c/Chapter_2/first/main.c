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

/* Example 2.3
 * In a company an employee is paid as under:
 * If his basic salary is less than Rs. 1500, then HRA = 10% of basic salary
 * and DA = 90% of basic salary. If his salary is either equal to or above
 * Rs. 1500, then HRA = Rs. 500 and DA = 98% of basic salary. If the
 * employee's salary is input through the keyboard write a program to find his
 * gross salary.*/
void grossSalary(int salaryEmployee)
{
    int condition = 1500;
    int hra, da, gross;
    if (salaryEmployee < condition)
    {
        hra = salaryEmployee * 10 / 100;
        da = salaryEmployee * 90 / 100;
    }
    else
    {
        hra = 500;
        da = salaryEmployee * 98 / 100;
    }
    gross = salaryEmployee + hra + da;
    printf("hra is %d\nda is %d\n", hra, da);
    printf("Gross salary is %d\n", gross);
}

/* Example 2.4
 * The marks obtained by a stydent in 5 different subjects are input
 * through the keyboard. The student gets a division as per the following
 * rules:
 * Percentage above or equal to 60 - First division
 * Percentage between 50 and 59 - Second division
 * Percentage between 40 and 49 - Third devision
 * Percentage less than 40 - Fail
 * Write a program to calculate the division obtained by the student
 * There are two ways in which we can write a program for this example */
// Method 1
void divisionObtained(int s1, int s2, int s3, int s4, int s5)
{
    int persent;
    persent = (s1 + s2 + s3 + s4 + s5) / 5;
    if (persent >= 60)
        puts("First division");
    else
    {
        if (persent >= 50)
            puts("Second division");
        else
        {
            if (persent >= 40)
                puts("Third division");
            else
                puts("Fail");
        }
    }

}
// Method 2
void divisionObtained2(int s1, int s2, int s3, int s4, int s5)
{
    int persent;
    persent = (s1 + s2 + s3 + s4 + s5) / 5;
    if (persent >= 60)
        puts("First division");
    if ((persent >= 50) && (persent < 60))
        puts("Second division");
    if ((persent >= 40) && (persent < 50))
        puts("Third division");
    if (persent < 40)
        puts("Fail");

}
// Method with else if
void divisionObtained3(int s1, int s2, int s3, int s4, int s5)
{
    int persent;
    persent = (s1 + s2 + s3 + s4 + s5) / 5;
    if (persent >= 60)
        puts("First division");
    else if (persent >= 50)
        puts("Second division");
    else if (persent >= 40)
        puts("Third division");
    else
        puts("Fail");
}

/* Example 2.5
 * A company insures its drivers in the following cases:
 * - If the driver is married.
 * - If the driver is unmarried, male & above 30 years of age.
 * - If the driver is unmarried, female & above 25 years of age.
 * Ii all other cases the driver isn't insured. If the marital status,
 * sex and age of the driver are the inputs, write a program to
 * determine whether the driver is to be insured or not.*/
void insuredDriver(char sex, char marriedS, int age)
{
    if (marriedS == 'M')
        puts("Insure");
    else if (sex == 'M' && age > 30)
        puts("Insure");
    else if (sex == 'F' && age > 25)
        puts("Insure");
    else
        puts("Driver is not insured");
}
void insuredDriver2(char sex, char marriedS, int age)
{
    if ((marriedS == 'M') || ((sex == 'M') && (age > 30)) ||
            ((sex == 'F') && (age > 25)))
        puts("Insure");
    else
        puts("Driver is not insured");
}

/* Example 2.6
 * Write a program to calculate the salary as per the following table*/
void tableSalary(char g, int yos, int qual)
{
    int sal;
    if (g == 'M' && yos >= 10 && qual == 1)
        sal = 15000;
    else if ((g == 'M' && yos >= 10 && qual == 0) ||
            (g == 'M' && yos < 10 && qual == 1))
        sal = 10000;
    else if (g == 'M' && yos < 10 && qual == 0)
        sal = 7000;
    else if (g == 'F' && yos >= 10 && qual == 1)
        sal = 12000;
    else if (g == 'F' && yos >= 10 && qual == 0)
        sal = 9000;
    else if (g == 'F' && yos < 10 && qual == 1)
        sal = 10000;
    else if (g == 'F' && yos < 10 && qual == 0)
        sal = 6000;
    printf("%d\n", sal);
}

/* Using ? and :*/
void example(int y)
{
    int x;
    x = (y <= 10 ? 0 : 1);
    printf("%d\n", x);
}

int main()
{
    return 0;
}
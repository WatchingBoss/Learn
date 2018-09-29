/* Exercises. Author: Egor */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Exercise a.
 * Program to calculate gross salary*/
void grossSalary(int x)
{
    float grossS;
    float dearnessAllow, rentAllow;
    dearnessAllow = 0.4f * x;
    rentAllow = 0.2f * x;
    grossS = x + dearnessAllow + rentAllow;
    printf("%.1f\n", grossS);
}

/* Exercise b
 * Program to convert km to other*/
void convertor(float km)
{
    float meters, feet, inches, centimeters;
    meters = km * 1000;
    feet = km * 3280.84f;
    inches = km * 39370.1f;
    centimeters = km * 1000000;
    printf("In %.1f km: %.1f meters\n"
                   "%.1f feet\n"
                   "%.1f inches\n"
                   "%.1f centimeters\n",
           km, meters, feet, inches, centimeters);
}

/* Exercise c
 * Program to calculate aggregate marks and percentage marks*/
int marks(int math, int biology, int art, int dance, int speech)
{
    if (math > 100 || biology > 100 || art > 100 || dance > 100 || speech > 100)
    {
        puts("Input is not correct");
        return 0;
    }
    int aggregateMark;
    float percentageMark;
    aggregateMark = math + biology + art + dance + speech;
    percentageMark = aggregateMark / 500.0f * 100;
    printf("Aggregate is %d\n"
                   "percentage is %.2f\n",
           aggregateMark, percentageMark);

    return 0;
}

/* Exercise d
 * Program to covert Fahrenheit to Celsius*/
void temperature(float fahr)
{
    float cels;
    cels = (fahr - 32) * (5.0f / 9.0f);
    printf("The temperature is %.1f celsius\n", cels);
}

/* Exercise e
 * Program to calculate:
 * 1) Area and perimeter of the rectangle
 * 2) Area and circumference of the circle*/
void rectangle(float length, float breadth)
{
    float area, perimeter;
    area = length * breadth;
    perimeter = (length + breadth) * 2;
    printf("The area is %.2f and perimeter is %.2f\n", area, perimeter);
}
void circle(float radius)
{
    float pi = 3.14159265259f, circumf;
    double area;
    area = pi * pow(radius, 2);
    circumf = 2 * pi * radius;
    printf("The area is %.2f and circumference is %.2f\n", area, circumf);
}

/* Exercise f
 * Program to interchange the contents of C and D */
void interchange(int C, int D)
{
    int a, b;
    a = C, b = D;
    C = b, D = a;
    printf("Now C is %d and D is %d\n", C, D);
}

/* Exercise d
 * Program to calculate the sum of number's digits*/
int sumOfDigits(int number)
{
    int digit, sum, n;
    n = number;
    sum = 0;
    while(n != 0)
    {
        digit = n % 10;
        sum = sum + digit;
        n = n / 10;
    }
    printf("The sum digits of %d is %d\n", number, sum);
    return 0;
}

/* Exercise h
 * Program to reverse the number*/
void reverseNumber(int number)
{
    int digit, n, newNumber;
    n = number;
    newNumber = 0;
    while (n != 0)
    {
        digit = n % 10;
        newNumber = newNumber * 10 + digit;
        n = n / 10;
    }
    printf("The reverse of %d is %d\n", number, newNumber);
}

/* Exercise i
 * Obtain first and last digits of number*/
void firstLast(int number)
{
    int digit, n, first, last;
    n = number;
    while (n != 0)
    {
        digit = n % 10;
        if (n / number == 1)
            last = digit;
        else if (n / 10 < 1)
            first = digit;
        n = n / 10;
    }
    printf("First is %d and last is %d\n", first, last);
}

/* Exercise j
 * Programe to find total number of illiterate men and women*/
void illiterate(int total)
{
    float men, women, totalLiteracy, literateMen, literateWomen, illiterateMen, illiterateWomen;
    men = total * 0.52f;
    women = total - men;
    totalLiteracy = total * 0.48f;
    literateMen = total * 0.35f;
    literateWomen = totalLiteracy - literateMen;
    illiterateMen = men - literateMen;
    illiterateWomen = women - literateWomen;
    printf("Total literacy are %.0f\n"
                   "Literate men are %.0f\n"
                   "Literate women are %.0f\n",
           totalLiteracy, literateMen, literateWomen);
    printf("Illiterate men are %.0f\n"
                   "Illiterate women are %.0f\n", illiterateMen, illiterateWomen);
    if (literateMen + literateWomen + illiterateMen + illiterateWomen == total)
        printf("Total is %.0f. All right!\n",
               literateMen + literateWomen + illiterateMen + illiterateWomen);
}

/* Exercise k
 * Calculate total number of currency notes*/
void denominations(int amountWithdrawn)
{
    int a = 10, b = 50, c = 100;
    int amA = 0, amB = 0, amC = 0;
    int amountCashier = 0;
    while (amountCashier != amountWithdrawn)
    {
        if (amountWithdrawn - amountCashier >= c)
        {
            amountCashier +=  c;
            amC++;
        }
        if (amountWithdrawn - amountCashier < c && amountWithdrawn - amountCashier >= b)
        {
            amountCashier += b;
            amB++;
        }
        if (amountWithdrawn - amountCashier < b && amountWithdrawn - amountCashier >= a)
        {
            amountCashier += a;
            amA++;
        }
    }
    printf("For %d you need:\n"
               "%d of 100 denominations currency notes\n"
               "%d of 50 denominations currency notes\n"
               "%d of 10 denominations currency notes\n",
       amountWithdrawn, amC, amB, amA);
}

/* Exercise i
 * Program to find cost price of one item*/
void costPrice(float totalSell, float totalProfit)
{
    int amount = 15;
    float costAll, costItem;
    costAll = totalSell - totalProfit;
    costItem = costAll / 15;
    printf("One item is cost %.1f\n", costItem);
}

/* Exercise m
 * Program to addition one to each number's digit*/
void addOne(int number)
{
    int digit, n, newNumber;
    n = number;
    newNumber = 0;
    while (n != 0)
    {
        digit = n % 10;
        newNumber = newNumber * 10 + digit + 1;
        n /= 10;
    }
    n = newNumber;
    newNumber = 0;
    while (n != 0)
    {
        digit = n % 10;
        newNumber = newNumber * 10 + digit;
        n /= 10;
    }
    printf("Result is %d\n", newNumber);
}

int main()
{
    return 0;
}
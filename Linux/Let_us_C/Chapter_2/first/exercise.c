/* Exercise for chapter 2*/
#include <stdio.h>
#include <math.h>

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
/* Find day of week for every day, month and year*/
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

/* Exercise e
 * A five-digit number is entered through the keyboard. Write a program to obtain
 * the reversed number and to determine whether the original and reversed
 * numbers are equal or not.*/
void reverseNumber(int number)
{
    int n, digit, newNumber;
    n = number;
    newNumber = 0;
    while (n != 0)
    {
        digit = n % 10;
        newNumber = newNumber * 10 + digit;
        n /= 10;
    }
    printf("Reverse number is %d\n", newNumber);
    if (newNumber == number)
        printf("%d is equal by %d\n", newNumber, number);
    else
        printf("%d is not equal by %d\n", newNumber, number);
}

/* Exercise f
 * If the ages of Ram, Shyam and Ajay are input through the keyboard, write
 * a program to determine the youngest of the three.*/
void youngest(int Ram, int Shyam, int Ajay)
{
    if (Ram < Shyam && Ram < Ajay)
        puts("Ram is youngest");
    else if (Shyam < Ram && Shyam < Ajay)
        puts("Shyam is youngest");
    else if (Ajay < Ram && Ajay < Shyam)
        puts("Ajay is youngest");
}

/* Exercise g
 * Write a program to check whether a triangle is valid or not, when the three
 * angles of the triangle are entered through the keyboard. A triangle is valid
 * if the sum of all the three angles is equal to 180 degrees.*/
void triangle(int a1, int a2, int a3)
{
    int sum = a1 + a2 + a3;
    if (sum == 180)
        puts("It is triangle!");
    else
        puts("You are wrong man!");
}

/* Exercise h
 * Find the absolute value of a number entered through the keyboard*/
void absoluteV(int number)
{
    int newN;
    if (number < 0)
        newN = number + number * (-2);
    else
        newN = number;
    printf("The absolute value is %d\n", newN);
}

/* Exercise i
 * Given the length and breadth of a rectangle, write a program to find whether
 * the area of the rectangle is greater then its perimeter.*/
void argrper(int length, int breadth)
{
    int area, per;
    area = length * breadth;
    per = (length + breadth) * 2;
    if (area < per)
        puts("Area is less than perimeter");
    else if (area == per)
        puts("Area is equal by perimeter");
    else
        puts("Area is greater than perimeter");
}

/* Exercise j
 * Given three points (x1, y1), (x2, y2), (x3, y3), write a program to check
 * if all the three points fall on one straight line.*/
void straightLine(int x1, int y1, int x2, int y2, int x3, int y3)
{
    if ((y2 - y1) / (x2 - x1) == (y3 - y2) / (x3 - x2))
        puts("Points are on one straight line");
    else
        puts("There is not straight line!!!!!!!!");
}

/* Exercise k
 * Given the coordinates (x, y) of a center of a circle and it's radius,
 * write a program which will determine whether a point lies inside the circle,
 * on the circle or outside the circle.*/
void pointAndCircle(int pX, int pY)
{
    int x = 0, y = 0, r = 10;
    double dist;
    dist = sqrt(pow((pX - x), 2) + pow((pY - y), 2));
    if (dist < r)
        puts("Point is inside the circle");
    else if (dist == r)
        puts("Point is on the circle");
    else
        (puts("Point is outside the circle"));
}

/* Exercise l
 * Given a point (x, y) write a program to find out if it lies on the x-axis,
 * y-axis or at the origin, viz. (0, 0)*/
void abscissa(int x, int y)
{
    if (x == 0 && y != 0)
        puts("Point lies on y-axis");
    else if (x != 0 && y == 0)
        puts("Point lies on x-axis");
    else if (x == 0 && y == 0)
        puts("Point is at the origin");
    else
        puts("Point doesn\'t lie on any axis");
}

/* F. Attempt the following.
 * Exercise a
 * Any year is entered through the keyboard, write a program to determine
 * whether the year is leap or not. Use the logical operators && and ||*/
void FA(int year)
{
    if ((year % 400 == 0) || (year % 100 != 0) && (year % 4 == 0))
        printf("%d is leap year. It has 366 days\n", year);
    else
        printf("%d is not leap year. It has 365 days\n", year);
}

/* Exercise b
 * Any character is entered through the keyboard, write a program to determine
 * whether the character entered is a capital letter, a small case letter,
 * a digit or a special symbol. Using ASCII values*/
void ascii(int symbol)
{
    if (symbol < 90 && symbol > 65)
        printf("%c is capital letter\n", symbol);
    else if (symbol < 122 && symbol > 97)
        printf("%c is small case letter\n", symbol);
    else if (symbol < 57 && symbol > 48)
        printf("%c is number\n", symbol);
    else if ((symbol > 0 && symbol < 47) || (symbol > 58 && symbol < 64) ||
            (symbol > 91 && symbol < 96) || (symbol > 123) && (symbol < 127))
        printf("%c is special symbol\n", symbol);
}

/* Exercise c
 * An Insurance company follows following rules to calculate premium*/
void premium(char health, int age, char lives, char sex)
{
    if (health == 'E' && (age > 25 && age < 35) && lives == 'C' && sex == 'M')
        puts("4 per thousand and 2 lakhs");
    else if (health == 'E' && (age > 25 && age < 35) && lives == 'C' && sex == 'F')
        puts("3 per thousand and 1 lakhs");
    else if (health == 'P' && (age > 25 && age < 35) && lives == 'V' && sex == 'M')
        puts("6 per thousand and 10000");
    else
        puts("The person is not insured");
}

/* Exercise d
 * Write a program, which will require the user to give values of hardness,
 * carbon content and tensile strength of the steel under consideration
 * and output the grade of the steel*/
void steelGrade(int hard, float carbon, int tensile)
{
    if (hard > 50 && carbon < 0.7 && tensile > 5600)
        puts("Grade is 10");
    else if (hard > 50 && carbon < 0.7)
        puts("Grade is 9");
    else if (carbon < 0.7 && tensile > 5600)
        puts("Grade is 8");
    else if (hard > 50 && tensile > 5600)
        puts("Grade is 7");
    else if (hard > 50 || carbon < 0.7 || tensile > 5600)
        puts("Grade is 6");
    else
        puts("Grade is 5");
}

/* Exercise e
 * Write a program to accept the number of days the member is late to return
 * the book and display the fine or the appropriate message*/
void libraryMember(int days)
{
    if (days < 5)
        puts("Pay 50 paise");
    else if (days > 5 && days < 10)
        puts("Pay 1 rupee");
    else if (days > 10)
        puts("Pay 5 rupees");
    if (days > 30)
        puts("Your membership will be cancelled");
}

/* Exercise f
 * Program to check valid of triangle*/
void triangleValid(int s1, int s2, int s3)
{
    if (s1 > s2 && s1 > s3)
    {
        if (s1 < s2 + s3)
            puts("It is triangle");
        else
            puts("It is not triangle");
    }
    else if (s2 > s1 && s2 > s3)
    {
        if (s2 < s1 + s3)
            puts("It is triangle");
        else
            puts("It is not triangle");
    }
    else if (s3 > s1 && s3 > s2)
    {
        if (s3 < s1 + s2)
            puts("It is triangle");
        else
            puts("It is not triangle");
    }
}

/* Exercise g
 * Program to check whether the is isosceles, equilateral, scalene or
 * right angled triangle*/
void checkTriangle(int s1, int s2, int s3)
{
    if (s1 == 90 || s2 == 90 || s3 == 90)
        puts("Triangle is right angled");
    else if (s1 == s2 && s2 == s3)
        puts("Triangle is equilateral");
    else if (s1 == s2 || s1 == s3 || s2 == s3)
        puts("Triangle is isosceles");
    else if (s1 != s2 != s3)
        puts("Triangle is scalene");
}

/* Exercise h
 * Program to find efficiency of workers*/
void efficiencyWoker(float time)
{
    if (time >= 2 && time < 3)
        puts("Worker is highly efficient");
    else if (time >= 3 && time < 4)
        puts("Worker should improve speed");
    else if (time >= 4 && time < 5)
        puts("Worker is given training to improve his speed");
    else if (time >= 5)
        puts("Worker is fired and leace the company!");
}

/* Exercise i
 * Program to receive marks in A and b*/
void qualify(int main, int subsidiary)
{
    if (main >= 55 && subsidiary >= 45)
        puts("Student is cool guy");
    else if (main < 55 && main >= 45 && subsidiary >= 55)
        puts("Student is cool guy but could better");
    else if (main >= 65 && subsidiary < 45)
        puts("Student should reappear in an examination in B to qualify");
    else
        puts("Student has failed");
}

/* Exercise j
 * Program to implement the company policy*/
void companyPolicy(int order, char credit)
{
    int stock = 50;
    if (order <= stock && credit == 'O')
        puts("Supply has requirement");
    else if (credit == 'N')
        puts("Not supply");
    else if (credit == 'O' && order > stock)
        puts("Data the balance will be shipped");
}

/* J. Attempt the following
 * Exercise a
 * Using conditional operators determine*/
void JA(char symbol)
{
    (symbol < 122 && symbol > 97) ? printf("%c is lower case alphabet\n", symbol)
    : ((symbol > 0 && symbol < 47) || (symbol > 58 && symbol < 64) ||
    (symbol > 91 && symbol < 96) || (symbol > 123 && symbol < 127))
    ? printf("%c is special symbol\n", symbol) : printf("Not\n");
}

/* Exercise b
 * Program to determine the year is leap or not*/
void JB(int year)
{
    (year % 400 == 0) ? printf("%d is leap\n", year) :
    (year % 100 == 0) ? printf("%d is not leap\n", year) :
    (year % 4 == 0) ? printf("%d is leap\n", year) :
    printf("%d is not leap\n", year);
}

/* Exercise c
 * Program to find the greatest of the three numbers*/
void JC(int n1, int n2, int n3)
{
    (n1 > n2 && n1 > n3) ? printf("%d is the greatest\n", n1) :
    (n2 > n1 && n2 > n3) ? printf("%d is the greatest\n", n2) :
    (n3 > n1 && n3 > n2) ? printf("%d is the greatest\n", n3) :
    puts("Done");
}

int main()
{
    return 0;
}
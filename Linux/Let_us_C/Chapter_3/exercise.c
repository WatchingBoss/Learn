/* Exercises for chapter 3*/
#include <stdio.h>
#include <math.h>

/*B. Attempt the following */
/* Exercise a
 * Program to calculate overtime pay of 10 employees*/
void BA()
{
    int overTime, workTime, i, overPay;
    overPay = 0;
    for (i = 0; i < 10; i++)
    {
        printf("Enter time of work in hour");
        scanf("%d", &workTime);
        if (workTime > 40)
        {
            overTime = workTime - 40;
        }
        overPay += overTime * 12;
    }
    printf("The overtime pay for 10 employees is %d\n", overPay);
}

/* Program to find factorial value of any number*/
void BB(int num)
{
    int i;
    long long int fNum = num;
    for (i = num - 1; i > 1; i--)
        fNum *= i;
    printf("The factorial of %d is %lld\n", num, fNum);
}

/*int t;
    int a[200]; //array will have the capacity to store 200 digits.
    int n,i,j,temp,m,x;

    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        a[0]=1;  //initializes array with only 1 digit, the digit 1.
        m=1;    // initializes digit counter

        temp = 0; //Initializes carry variable to 0.
        for(i=1;i<=n;i++)
        {
            for(j=0;j<m;j++)
            {
                x = a[j]*i+temp; //x contains the digit by digit product
                a[j]=x%10; //Contains the digit to store in position j
                temp = x/10; //Contains the carry value that will be stored on later indexes
            }
            while(temp>0) //while loop that will store the carry value on array.
            {
                a[m]=temp%10;
                temp = temp/10;
                m++; // increments digit counter
            }
        }
        for(i=m-1;i>=0;i--) //printing answer
            printf("%d",a[i]);
        printf("\n");
    }*/

/* Exercise c
 * Program to find the calue of one number raised to the power of another*/
void BC()
{
    int num, p;
    char answ;
    double result;
    do {
        printf("Enter number and value of power");
        scanf("%d %d", &num, &p);
        result = pow(num, p);
        printf("The result is %.0f\n", result);
        printf("Do you want enter other numbers? y/n\n");
        fgetc(stdin);
        scanf("%c", &answ);
    } while (answ == 'y' || answ == 'Y');
}

/* Exercise d
 * Program to print all the ASCII values and their equivalent characters*/
void BD()
{
    int i = 0;
    while (i <= 255)
    {
        printf("%d %c\n", i, i);
        i++;
    }
}

/* Exercise e
 * Program to print out Armstrong numbers*/
void BE(int i)
{
    int x = 1, digit, n, a, b, c;
    double sum;
    while (x <= i)
    {
        if (x >= 100)
        {
            n = x;
            digit = n % 10;
            a = digit;
            n /= 10;
            digit = n % 10;
            b = digit;
            n /= 10;
            c = n;
            sum = pow(a, 3) + pow(b, 3) + pow(c, 3);
            if (sum == x)
                printf("%d is Armstrong number\n", x);
        }
        x++;
    }
}

/* Exercise f
 * Program for a matchstick game*/
void BF()
{
    int ms = 21, user, comp;
    while (ms >= 1)
    {
        if (ms == 1)
        {
            printf("Matchstick\'s amount is %d. You are loser\n", ms);
            break;
        }
        printf("Enter matchstick amount (1, 2, 3, 4)\n");
        scanf("%d", &user);
        if (user <= 0 || user >= 5)
        {
            printf("Invalid value\n");
            break;
        }
        printf("You pick %d matchsticks\n", user);
        ms -= user;
        printf("The amount of matchsticks is %d\n", ms);
        comp = 5 - user;
        printf("Computer pick %d matchsticks\n", comp);
        ms -= comp;
        printf("The amount of matchsticks is %d\n", ms);
    }
}

/* Exercise g
 * Program to display the count of positive, negative and zeros entered*/
void BG()
{
    int num, p = 0, n = 0, z = 0;
    char answer;
    do
    {
        printf("Enter number");
        scanf("%d", &num);
        if (num < 0)
            n++;
        else if (num == 0)
            z++;
        else if (num > 0)
            p++;
        fgetc(stdin);
        printf("Do you want to continue? Y/N");
        scanf("%c", &answer);
    } while (answer == 'y' || answer == 'Y');
    printf("The count of positive is %d, negative is %d and zeros is %d\n", p, n, z);
}

/* Exercise h
 * Program to find the octal equivalent of the entered number*/
/*void BH(int number)
{
    int n = number;
    if (n >= 4096 && n < 32768)
    {
        int d1, d2, d3, d4, d5;
        d1 = n / 4096;
        n -= d1 * 4096;
        d2 = n / 512;
        n -= d2 * 512;
        d3 = n / 64;
        n -= d3 * 64;
        d4 = n / 8;
        n -= d4 * 8;
        d5 = n;
        printf("%d in decimal is %d%d%d%d%d in octal\n", number, d1, d2, d3, d4, d5);
    }
    else if (n >= 512 && n < 4096)
    {
        int d1, d2, d3, d4;
        d1 = n / 512;
        n -= d1 * 512;
        d2 = n / 64;
        n -= d2 * 64;
        d3 = n / 8;
        n -= d3 * 8;
        d4 = n;
        printf("%d in decimal is %d%d%d%d in octal\n", number, d1, d2, d3, d4);
    }
    else if (n >= 64 && n < 512)
    {
        int d1, d2, d3;
        d1 = n / 64;
        n -= d1 * 64;
        d2 = n / 8;
        n -= d2 * 8;
        d3 = n;
        printf("%d in decimal is %d%d%d in octal\n", number, d1, d2, d3);
    }
    else if (n > 8 && n < 64)
    {
        int d1, d2;
        d1 = n / 8;
        n -= d1 * 8;
        d2 = n;
        printf("%d in decimal is %d%d in octal\n", number, d1, d2);
    }
    else if (n <= 8)
    {
        int d1;
        d1 = n ;
        printf("%d in decimal is %d in octal\n", number, d1);
    }
}*/

/*void BH(int number)
{
    int n = number, digit, octal = 0;
    while (n > 0)
    {
        digit = n - (n / 8 * 8);
        n /= 8;
        octal = octal * 10 + digit;
    }
    n = octal;
    octal = 0;
    while(n > 0)
    {
        digit = n % 10;
        n /= 10;
        octal = octal * 10 + digit;
    }
    printf("%d in decimal is %d in octal\n", number, octal);
}*/

void BH(long number)
{
    long n;
    int octal[100], i = 1, j;
    while (n != 0)
    {
        octal[i++] = n % 8;

    }
}

int main()
{
    BH(4096);
    return 0;
}
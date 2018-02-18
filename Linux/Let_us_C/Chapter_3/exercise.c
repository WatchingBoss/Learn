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

void BH(int number)
{
    int n = number;
    int octal[5], i = 1, j;
    while (n != 0)
    {
        octal[i++] = n % 8;
        n /= 8;
    }
    printf("The %i in decimal is ", number);
    for (j = i - 1; j > 0; j--)
        printf("%d", octal[j]);
    puts(" in octal");
}

/* Exercise i
 * Program to find the range of a set of numbers*/
void BI()
{
    int min = 32767, max = -32768, num, range;
    char ans;
    do {
        printf("Enter number\n");
        scanf("%d", &num);
        if (num > max)
            max = num;
        if (num < min)
            min = num;
        printf("Do you want to enter another number? y/n\n");
        fgetc(stdin);
        scanf("%c", &ans);
    } while (ans == 'y' || ans == 'Y');
    range = max - min;
    printf("Range between %d and %d is %d", min, max, range);
}

/* E. Attempt the following*/
/* Exercise a
 * Program to print all prime numbers from 1 to n*/
void EA()
{
    int num, max, check = 2;
    printf("Enter first and last numbers");
    scanf("%d %d", &num, &max);
    while (num <= max)
    {
        while (check < num)
        {
            if (num % check == 0 && check < num)
            {
                break;
            }
            check++;
        }
        if (check == num)
            printf("%d is prime number\n", num);
        num++;
        check = 2;
    }
}

/* Exercise b
 * Program to fill the entire screen with a smiling face*/
void EB()
{
    char smile = 1;
    for (int i = 1; i < 15; i++)
    {
        for (int f = 1; f < 100; f++)
            printf("%c", smile);
        puts("");
    }
}


/* Exercise c
* Program to add dirst seven terms of the following series
* 1/1! + 2/2! + 3/3! + ...*/
void EC()
{
    float f;
    float sum = 0;
    for (int i = 1; i <= 7; i++)
    {
        f = 1;
        for (int n = i; n > 0; n--)
        {
            f *= n;
        }
        printf("%d/%.0f is %.5f\n", i, f, i / f);
        sum += i / f;
    }
    printf("Result is %.5f\n", sum);
}

/* Exercise d
 * Program to generate all combinations of 1, 2 and 3*/
/*void EC()
{
    int z, x, c;
    for (z = 1; z <= 3; z++)
    {
        for (x = 1; x <= 3; x++)
        {
            for (c = 1; c <= 3; c++)
            {
                if (z != x && z != c && x != c)
                    printf("%d%d%d\n", z, x, c);
            }
        }
    }
}*/
void print(int *num, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d", num[i]);
    printf("\n");
}
void ED()
{
    int num[3], temp, i, n, j;
    printf("How many numbers you want to enter: ");
    scanf("%d", &n);
    printf("Enter a list of numbers to see all combinations: ");
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    for (j = 1; j <= n; j++)
    {
        for (i = 0; i < n - 1; i++)
        {
            temp = num[i];
            num[i] = num[i + 1];
            num[i + 1] = temp;
            print(num, n);
            for (int k = 0; k < n; k++)
                printf("%d", num[k]);
            printf("\n");
        }
    }
}

/* Exercise e
 * Program to produce a table of values of formula*/
void EE()
{
    float i, x;
    int j, y;
    puts("--------------------------------");
    for (y = 1; y <= 6; y++)
    {
        x = 5.5;
        for (j = 1; j <= 15; j++)
        {
            i = 2 + (y + 0.5f * x);
            printf("| i = %4.1f | y = %2d | x = %4.1f |\n", i, y, x);
            x += 0.5;
        }
        puts("--------------------------------");
    }

}

/* Exercise f
 * Program to produce figure from alphabets*/
void EF()
{
    char letter[] = {65, 66, 67, 68, 69, 70, 71};
    int alphabet;
    for (int l = 6; l > 0; l--)
    {
        for (int i = 0; i <= 6; i++)
            printf("%c ", letter[i]);
        for (int i = 5; i >= 0; i--)
            printf("%c ", letter[i]);
        puts("");
        letter[l] = ' ';
    }
    for (int l = 0; l <= 7; l++)
    {
        for (int i = 0; i <= 6; i++)
            printf("%c ", letter[i]);
        for (int i = 5; i >= 0; i--)
            printf("%c ", letter[i]);
        puts("");
        alphabet = 65 + l;
        letter[l] = alphabet ;
    }
}

/* Exercise g
 * Program to fill the entire screen with alphabets diamond and heart*/
void EG()
{
    for (int i = 0; i < 6; i++)
    {
        for (int d = 0; d < 2; d++)
        {
            for (int s = 6 - i; s > 0; s--)
                printf("%c ", 3);
            for (int s = i * 4; s > 0; s--)
                printf("%c", ' ');
            for (int s = 6 - i; s > 0; s--)
                printf("%c ", 3);
        }
        puts("");
    }
    for (int i = 5; i >= 0; i--)
    {
        for (int d = 0; d < 2; d++)
        {
            for (int s = 6 - i; s > 0; s--)
                printf("%c ", 4);
            for (int s = i * 4; s > 0; s--)
                printf("%c", ' ');
            for (int s = 6 - i; s > 0; s--)
                printf("%c ", 4);
        }
        puts("");
    }
}

/* Exercise h
 * Program to print the multiplication table of the number entered by the user.*/
void EH()
{
    int number, multi;
    printf("Enter some number and max value for multiplication: ");
    scanf("%d %d", &number, &multi);
    for (int i = 1; i <= multi; i++)
    {
        printf("%d * %d = %d\n", number, i, number * i);
    }
}

/* Exercise i
 * Program to produce output*/
void EI(int l)
{
    int n = 1, s;
    for (int i = 1; i <= l; i++)
    {
        for (s = (l - i) * 2; s > 0; s--)
            printf(" ");
        for (int p = i; p > 0; p--)
        {
            printf("%-4d", n);
            n++;
        }
        puts("");
    }
}

/* Exercise j
 * Program to produce the Pascal's triangle*/
/*void EJ(int n)
{
    for (int line = 1; line <= n; line++)
    {
        for (int j = (n - line) * 3; j > 0; j--)
            printf(" ");
        int C = 1; // used to represent C(line, i)
        for (int i = 1; i <= line; i++)
        {
            printf("%-6d", C); // The first value in a line is always 1
            C = C * (line - i) / i;
        }
        printf("\n");
    }
}*/

void EJ(int n)
{
    for (int l = 1; l <= n; l++)
    {
        for (int s = (n - l) * 2; s > 0; s--)
            printf(" ");
        int num = 1;
        for (int i = 1; i <= l; i++)
        {
            printf("%-3d ", num);
            num = num * (l - i) / i;
        }
        printf("\n");
    }
}

/* Exercise k
 * Program to calculate minimum count of years machine's life to make
 * investment to its more attractive*/
void EK()
{
    int cost = 6000 - 2000, yearEM = 1000, yearEA = yearEM * 12 / 100;
    int alt = 0, year = 0, inv = 0;
    do {
        year++;
        alt = yearEA * year;
        inv = yearEM * year - cost;
    } while (alt > inv);
    printf("After %d years investment to machine will brine %d and alternative - %d\n",
           year, inv, alt);
}

/* Exercise i
 * Program to read sets of p, r, n, q and calculate compound interest*/
void EL()
{
    int p, n, q;
    double r, a;
    for (int i = 0; i < 10; i++)
    {
        printf("Enter:\n"
                       "p (the money you start with, your first deposit)\n"
                       "r (the annual rate of interest as a decimal)\n"
                       "n (the number of years you leave it on deposit)\n"
                       "q (times of interest compounds per year)\n");
        scanf("%d %lf %d %d", &p, &r, &n, &q);
        a = p * (pow((1 + r / q), (n * q)));
        printf("After %d years you\'ll accumulate %.2lf", n, a);
    }
}

/* Exercise m
 * Program to calculate first seven terms of series of natural logarithm*/
void EM(double x)
{
    double sum = (x - 1) / x;
    for (int i = 2; i <= 7; i++)
    {
        sum += (0.5 * (pow(((x - 1) / x), i)));
    }
    printf("The sum equal %.2lf\n", sum);
}

int main()
{
    EM(10);
    return 0;
}
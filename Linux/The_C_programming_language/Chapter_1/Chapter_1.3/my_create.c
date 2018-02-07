#include <stdio.h>

/*Choose type of temperature and enter value*/
int main()
{
    float fahr, celsium;

    int num;

    puts("Choose type of temperature: \n"
                 "1 - Fahrenheit\n"
                 "2 - Celsius\n");
    scanf("%d", &num);

    if (num == 1) {

        puts("Enter number: ");
        scanf("%f", &fahr);
        printf("%3.1f F is %3.1f C\n", fahr, (5.0 / 9.0) * (fahr - 32));
    } else if (num == 2) {

        puts("Enter number: ");
        scanf("%f", &celsium);
        printf("%3.1f C is %3.1f F\n", celsium, celsium * (9.0 / 5.0) + 32);
    } else puts("Somethings is wrong:(");

    return 0;
}
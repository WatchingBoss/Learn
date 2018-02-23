#include <stdio.h>

void sw(int i)
{
    switch(i)
    {
	 case 1:
            printf("I am in case 1\n");
            break;
        case 2:
            printf("I am in case 2\n");
            break;
        case 3:
            printf("I am in case 3\n");
            break;
        default:
            printf("I am in default\n");
    }
}

void sc(char ch)
{
  switch(ch)
  {
  }
}
int main()
{
    sw(2);
    return 0;
}

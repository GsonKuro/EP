#include <stdio.h>

int print_bit(int num, int pos)
{
    if (((1<<pos)&num) == 0)
    {
        printf("O bit é zero\n");
    } else {
        printf("O bit é um\n");
    }
}

int main()
{
    int i;
    int p;

    printf("Write a integer:");
    scanf("%d",&i);
    printf("Write bit position:");
    scanf("%d",&p);

    print_bit(i,p);
}
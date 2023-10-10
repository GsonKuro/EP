#include <stdio.h>

void print_bits(int num)
{
    int bitArray[32];
    int i = 0;

    for (i = 0; num > 0; i++)
    {
        bitArray[i] = num%2;
        num /=2;
    }

    for ( int j = i-1; j>=0; j--)
    {
        printf("%d", bitArray[j]);
    }
    
    printf("\n");
}

int main()
{
    int i;
    int p;

    printf("Write a integer:");
    scanf("%d",&i);

    print_bits(i);
}
//afafafafafaf
#include <stdio.h>

int print_bits(int num)
{
    int bitArray[] = {};
    int rest;

    for (int i = 0; num < 1; i++)
    {
        rest = num%2;
        bitArray[i] = rest;
        num = num/2;
    }

    printf("O binaŕio é %d \n", rest);
    
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------//
//           Decimal -> Binary
//---------------------------------------//

int print_bits(int num)
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

//---------------------------------------//
//          Binary -> Decimal
//---------------------------------------//

int bits_to_int(char binary[32])
{
    int num = atoi(binary);
    int decimal = 0;

    for (int base = 1;  num > 0; base = base * 2)
    {
        int last_bit = num % 10;
        num = num / 10;

        decimal += last_bit * base;
    }

    printf("%d\n", decimal);

    return decimal;
}

//---------------------------------------//
//              Main Cycle
//---------------------------------------//

int main(int argc, char* argv[]){

    char binary[32];
    int i;
    printf("%s\n",argv[1]);

    if (strcmp(argv[1],"decimal") == 0){
        printf("Type a binary number to convert : ");
        scanf("%s", binary);
        bits_to_int(binary);
    }
    else if (strcmp(argv[1],"binary") == 0){
        printf("Type a decimal number to convert : ");
        scanf("%d", &i);
        print_bits(i);
    }
    
    return 0;
}
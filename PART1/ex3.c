#include <stdio.h>
#include <stdlib.h>

char bits_to_int(char binary[32])
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
}

int main()
{
    char binary[32];

    printf("Escreve um número em binário para sre convertido em decimal: ");
    scanf("%s", binary);
    bits_to_int(binary);
    return 0;
}

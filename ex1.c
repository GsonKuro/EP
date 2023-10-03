#include <stdio.h>

int main(){
    char c  = 'Z';
    char *p = &c;

    printf("O código ASCII do caracter %c é %d\n", c, c);
    printf("O endereço da variável c é %p\n", p);
    printf("O conteúdo do endereço %p  é %c\n", p, *p);
    return 0;
}
#include "types.h"
#include "defs.h"

static char *digits = "0123456789ABCDEF";

void puts(char *s) { // imprime String 
    while(*s != 0) { // enquanto não chegar ao fim da string 
        uartputc(*s); // chama a função uartputc para imprimir o caracter  no arquivo uart.c 
        s++; // incrementa o ponteiro para a próxima posição da string
    }
}

void printlng (long val, int base) {
    long l; // STRING QUE EH UM NUMERO QUE VAI SER TRANSFORMADO EM  CODIGO ASCII
    int i = 0;
    char s[66]; // TAMANHO DA STRING

     // SE FOR NUMERO NEGATIVO,
    if(val < 0 ) l = -val; //S CONTEM NUMERO INVERTIDO
    else l = val;

    while(l != 0) {
        //int d = l % 10; // PEGA O RESTO A DIVISAO DE L 
        //int cod_ascii = digits[d]; // OBTER O CÓDIGO ASCII CORRESPONDENTE AO DIGITO 
        //s[i++] = cod_ascii;
        //l = l/10; // DIVIDE POR 10 O QUOCIENTE DA 1º OPERACAO
        s[i++] = digits[l%base];
        l = l/base; 
    }

     //if(base == 16) {
        if(base == 2) {
        s[i++] = 'b';
        s[i++] = '0';
    } 
    
    if(val<0)
        s[i++] = '-';

    //S CONTEM O NUMERO INVERTIDO
    while(i > 0) { // QUANDOCHEGAR NO ULTIMO CARACTERE
        uartputc(s[--i]); // decrementa o i antes
    }
    //puts(s); 
}

void printptr( void *ptr) {
    uint64 addr = (uint64) ptr;
    char s[66];
    int i = 0;

    while (addr != 0) {
        s[i++] = digits[addr % 16];
        addr = addr/16;
    }
    s[i++] = 'x';
    s[i++] = '0';

    while(i > 0) { // QUANDOCHEGAR NO ULTIMO CARACTERE
        uartputc(s[--i]); // decrementa o i antes
    }
}


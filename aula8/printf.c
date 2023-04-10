#include <stdarg.h>
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

//FUNCAO PRINTF
void printf(char *fmt, ...) {
    va_list ap;
    int c;
    char *str;
    va_start(ap, fmt);

    for(; (c = *fmt) != 0; fmt++) {
        if(c == '%') {
            //em busca do formatador (d, l, p, s, x, %)
            //olha para o próximo caractere que vai definir o tipo do formatador
            c = *(fmt+1);
            fmt++; 
            //verificar se há caracteres após o %
            switch(c) {
                case '%':
                    uartputc(c);
                    break;

                case 'd':
                    printlng(va_arg(ap, int), 10);
                    break;

                case 'l':
                     printlng(va_arg(ap,long), 10);
                    break;

                case 'x':
                    printlng(va_arg(ap,int), 16);
                    break;

                case 'p':
                    printptr(va_arg(ap, void *));
                    break;

                case 's':
                    str = va_arg(ap, char *);
                    puts(str);
                    break;
                
            }

        }
        else {
            uartputc(c); //imprime a String 
        }
    }



}



int perimetro(int lados, ...) {
    va_list ap; //ponteiro para a lista de argumentos variáveis
    va_start(ap, lados); // ap aponta para inicio da lista que é N
    
    int per = 0;
    for(int i =0; i< lados; i++) { // percorre a pilha de lados de acordo com a quantidade de llados
        per += va_arg(ap, int); // soma a variavel per + va_arg que pega o inicio da pilha ap[i] e o tamanho do tipo em que ela tem que buscar o próximo
    }

    return per;
}


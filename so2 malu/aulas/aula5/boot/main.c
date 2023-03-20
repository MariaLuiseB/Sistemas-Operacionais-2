// imprimir olá mundo 
#include "types.h"
#include "defs.h"

void puts(char *s) {
    while(*s != 0) { // enquanto não chegar ao fim da string 
        uartputc(*s); // chama a função uartputc para imprimir o caracter  no arquivo uart.c 
        s++; // incrementa o ponteiro para a próxima posição da string
    }
}

void entry() { // o boot salta para a função entry
    puts("Olá mundo, disse o Kernel!"); // chama a função puts 

    // DIGITAR E LE -- INTERAÇÃO COM O USUÁRIO 
    int c;
    while (1) { // ENQUANTO VERDADEIRO 
        c = uargetc();
        if (c != -1) {
            uartputc(c);
        }
    }
    
}

// imprimir olá mundo 
#include "types.h"
#include "defs.h"
#include "console.h"

void puts(char *s) {
    while(*s != 0) { // enquanto não chegar ao fim da string 
        uartputc(*s); // chama a função uartputc para imprimir o caracter  no arquivo uart.c 
        s++; // incrementa o ponteiro para a próxima posição da string
    }
}

void entry() { // o boot salta para a função entry
    // uartputc(27); // 27 É A TECLA ESC
    // uartputc('['); // 1 CARACTER QUE VALE UM NUMERO
    // uartputc('2'); // 2 VEZES
    // uartputc('B'); // PARA BAIXO, B = BELOW
    puts(BOLD COLOR_BG COLOR_FG);
   
    puts(" \u03A9 <- Um Ômega!"); // chama a função puts 
    puts(" \u03B2 <- Um Beta!");
    puts(" \u03BB <- Um Lâmbda!");
    puts(" \u2764 <- Um Coraçon!");
    puts(NORMAL);
    // DIGITAR E LE -- INTERAÇÃO COM O USUÁRIO 
    int c;

    while (1) { // ENQUANTO VERDADEIRO 
        c = uargetc();
        if (c == -1) { // USUARIO NAO DIGITOU NADA
            continue; // VOLTA AO INICIO DO LAÇO 
            uartputc(c); // CHAMA A FUNÇÃO QUE IMPRIME OS CARACTERES 
        }

        // TECLAS DIFERENTES DO ALFABETO, BACKSPACE E ENTER
        switch(c) {
            case '\r': // DIGITOU ENTER
            uartputc('\r'); // r = 13 em ascii
            uartputc('\n'); // uartputc()
            break;

            case 127: // DIGITOU BACKSPACE 
            uartputc('\b'); // BACKSPACE
            uartputc(' '); // ESPACO 
            uartputc('\b'); // BACKSPACE
            break;

            default:
            uartputc(c);
            break;
        }
    }
    
}

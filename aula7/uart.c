#include "memlayout.h"
#include "types.h"

#define THR 0 // REGISTRADOR PARA TRANSMISSÃO DE DADOS
#define RBR 0 // REGISTRADOR PARA RECEPÇÃO DE DADOS
#define IER 1 // CONFIGURA INTERRUPÇÕES 
#define FCR 2  // CONFIGURA FIFO(BUFFER)
#define LCR 3 // CONFIGURA MODO DE OPERAÇÃO (TRANSMISSÃO DE 8 BITS)
#define LSR 5 // PRONTO PARA TRANSMISSÃO/RECEPÇÃO DE DADOS


char
read_reg(uint8 reg) {
    char c; 
     volatile uint8 *base = (uint8 *) UART;
    c = *(base + reg);
    return c;
}

void 
write_reg(uint8 reg, uint8 val) {
    volatile uint8 *base = (uint8 *) UART;
    *(base + reg) = val; 
}

void 
uartinit() { 
    //HABILITAR INTERRUPÇÃO
    write_reg(IER, 1);
    //HABILITAR A FIFO 
    write_reg(FCR, 1); 
    //HABILITA TRANSMISSÃO DE DADOS DE 8 BITS  
    write_reg(LCR, 3);
}

void 
uartputc(int c) { // IMPRIMIR CARACTERES NO TERMINAL VIA UART 
    // VERIFICAR SE O REGISTRADOR DE TRANSMISSÃO ESTÁ VAZIO ex: uartputc('c') -- imprime o caractere'c'
    while ((read_reg(LSR) & (1<<5)) == 0); // ENQUANTO FOR VERDADEIRO, NAO SAI DO WHILE, SE O REG 5 FOR IGUAL A 0, NAO ESCREVE 
    write_reg(THR, c); 
}

int //LÊ CARACTERES DO TERMINAL VIA UART
uargetc( ) {
    //VERIFICAR SE O REGISTRADOR DA RECEPÇÃO ESTÁ VÁZIO
    int c;
    if ((read_reg(LSR) & 1) == 0) return -1; // SE O REG LSR FOR == 0, RETORNA -1
    c = read_reg(RBR);
    return c;
}
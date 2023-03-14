// imprimir olá mundo 

static void putc (char c) {
    char *r; // ponteiro para char
    r = (char *) 0x10000000; // endereço de memória do primeiro caracter da tela
    *r = c; // coloca o caracter na posição de memória 0x10000000
}

void puts(char *s) {
    while(*s != 0) { // enquanto não chegar ao fim da string 
        putc(*s); // chama a função putc para imprimir o caracter
        s++; // incrementa o ponteiro para a próxima posição da string
    }
}

void entry() { // o boot salta para a função entry
    puts("Olá mundo, disse o Kernel!"); // chama a função puts 
}

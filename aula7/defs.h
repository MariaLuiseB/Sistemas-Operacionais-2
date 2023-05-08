//DECLARAÇÕES DE FUNÇÕES DO KERNEL QUE SÃO UTILIZADAS EM VÁRIOS LUGARES SÃO DEFINIDAS AQUI 

void uartinit(); // INICIALIZAR O UART 
void  uartputc(int c); // IMPRIME CARACTERES NO TERMINAL VIA UART
int uargetc( ) ; //LÊ CARACTERES DO TERMINAL VIA UART

//FUNÇÕES DE IMPRESSÃO DE ALTO NIVEL     
void printlng(long, int);
void printptr(void *);
void puts(char *s);


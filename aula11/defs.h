//DECLARAÇÕES DE FUNÇÕES DO KERNEL QUE SÃO UTILIZADAS EM VÁRIOS LUGARES SÃO DEFINIDAS AQUI 

void uartinit(); // INICIALIZAR O UART 
void  uartputc(int c); // IMPRIME CARACTERES NO TERMINAL VIA UART
int uargetc( ) ; //LÊ CARACTERES DO TERMINAL VIA UART

//FUNÇÕES DE IMPRESSÃO DE ALTO NIVEL     
void printlng(long, int);
void printptr(void *);
void puts(char *s);

//FUNÇÃO PRINTF
void printf(char *fmt, ...);

//FUNÇÃO QUE QUEREMOS IMPLEMENTAR: FUNÇÃO VARIADIC
int perimetro (int lados, ...); // n -> quantidade de lados e ... -> valores de cada lado que foi colocado no 1º parâmetro

//GERENCIAMENTO DE MEMÓRIA (Kalloc, kfree)
void memory_init();
void pages_init();
void* kalloc (int);

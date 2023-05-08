#include "defs.h"
#include "types.h"
#include "memlayout.h"

extern uint64 stack_start[];
extern uint64 stack_end[];
extern uint64 text_end[];

#define HEAP_START stack_end
#define HEAP_END (uint8 *) (KERNEL_START + MEMORY_LENGTH)
#define HEAP_SIZE ( (uint64) HEAP_END - (uint64)HEAP_START )
#define FREE_PAGE 0x01
#define LAST_PAGE 0x02

long total_pages; //Número total de páginas do heap
long alloc_start; //Início da região alocável do heap

int free_page(uint8 desc) { //Verifica se a página referenciada por desc está livre 
    if(desc & FREE_PAGE) return 1;
    return 0; 
}

int last_page (uint8 desc) {//Verifica se é a ultima página de um bloco
    if(desc & LAST_PAGE) return 1;
    return 0;
}

int set_free_page_flag(uint8 *desc, uint8 freedom) {//Marcar página como livre/ocupada
    if(freedom == 1)
        *desc = *desc | FREE_PAGE;
    else 
        *desc = *desc & (0xFF << 1); // OU ~FREE_PAGE  
}

void set_last_page_flag(uint8 *desc, uint8 last) {
    if(last) 
        *desc = *desc | LAST_PAGE;
    else // bit 1 p/ 0
        *desc = *desc & ~LAST_PAGE; // DESC & 11111101, LAST_PAGE = 11111101
       //*desc = *desc & ( (0xFF << 2) | 1); 
}

//Cria e Inicializa descritores da página
int pages_init() {
    uint8 *desc = (uint8 *)HEAP_START; // Aponta para um descritor
    int reserved_pages = 0; //páginas não alocáveis(p/ os descritores)
    int total_pages = HEAP_SIZE/PAGE_SIZE; 
    reserved_pages = total_pages/PAGE_SIZE; // descritores 
    if(total_pages % PAGE_SIZE) reserved_pages++;
    total_pages -= reserved_pages; // total de páginas alocáveis
    int i;
    for(i=0; i<total_pages; i++) {
        desc[i] = FREE_PAGE;
    }
    printf("Páginas reservadas aos descritores: %d\n", reserved_pages );
    printf("Páginas Livres: %d\n", total_pages);
    alloc_start = (uint64)HEAP_START + reserved_pages * PAGE_SIZE;
}


void memory_init() {
    //Area de Código
    printf("Código:\n");
    printf("\tInicio:\t \t%p\n", KERNEL_START);
    printf("\tFim:\t \t%p\n", text_end);
    printf("\tTamanho:\t %d\n", (uint64)text_end - KERNEL_START);
    //Area de Dados
    printf("Dados:\n");
    printf("\t Inicio:\t %p\t\n", text_end);
    printf("\t Fim:\t \t%p\n", stack_start);
    printf("\t Tamanho:\t \t%d\n", (uint64)stack_start - (uint64)text_end);
    //Area da Pilha
    printf("Pilha:\n");
    printf("\t Início:\t \t%p\n", stack_start);
    printf("\t Fim: \t \t%p\n", stack_end);
    //Área do Heap
    printf("Heap:\n");
    printf("\t Início:\t \t%p\n", HEAP_START);
    printf("\t Fim:\t \t%p\n", HEAP_END);
    printf("\tTamanho:\t \t%d\n", HEAP_SIZE);
    printf("\tTamanho em MB:\t \t%d\n", HEAP_SIZE/1024/1024);

}

//inicializa os descritores.
pages_init();

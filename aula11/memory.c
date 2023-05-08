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

void set_free_page_flag(uint8 *desc, uint8 freedom) {//Marcar página como livre/ocupada
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

/* Arredonda o endereço para o múltiplo de PAGE_SIZE mais próximo (para CIMA)
    page_round(4095) -> 496
    page_roung(4096) -> 4096
    page_roung(5001) -> 8192
*/

uint64
page_round_up (uint64 addr) {
    if (addr % PAGE_SIZE == 0) return addr; // end já é multiplo de PAGE_SIZE
    return addr - (addr % PAGE_SIZE) + PAGE_SIZE; // arredonda para cima para que ele seja multiplo de PAGE_SIZE
}

/* Arredonda o endereço para o múltiplo de PAGE_SIZE mais próximo (para CIMA)
    page_round(4095) -> 0
    page_roung(4096) -> 4096
    page_roung(5001) -> 4096
*/

uint64
page_round_down (uint64 addr) {
    if (addr % PAGE_SIZE == 0) return addr; // end já é multiplo de PAGE_SIZE
    return addr - (addr % PAGE_SIZE); // arredonda para cima para que ele seja multiplo de PAGE_SIZE
}

//Cria e Inicializa descritores da página
void pages_init() {
    uint8 *desc = (uint8 *)HEAP_START; // Aponta para um descritor
    int reserved_pages = 0; //páginas não alocáveis(p/ os descritores)
    total_pages = HEAP_SIZE/PAGE_SIZE; 
    reserved_pages = total_pages/PAGE_SIZE; // descritores 
    if(total_pages % PAGE_SIZE) reserved_pages++;
    total_pages -= reserved_pages; // total de páginas alocáveis
    int i;
    for(i=0; i<total_pages; i++) {
        desc[i] = FREE_PAGE;
    }
    printf("Páginas reservadas aos descritores: %d\n", reserved_pages );
    printf("Páginas Livres: %d\n", total_pages);
    alloc_start = page_round_up((uint64)HEAP_START + reserved_pages * PAGE_SIZE);
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
    printf("\t Fim:\t \t%p\n", stack_end);
    //Área do Heap
    printf("Heap:\n");
    printf("\t Início:\t \t%p\n", HEAP_START);
    printf("\t Fim:\t \t%p\n", HEAP_END);
    printf("\tTamanho:\t \t%d\n", HEAP_SIZE);
    printf("\tTamanho em MB:\t \t%d\n", HEAP_SIZE/1024/1024);

    pages_init();

    printf("Inicio da região alocável do heap: %p\n", alloc_start);
    printf("Arredondamento para cima de %d: %d\n", 4077, page_round_up(4077));
    printf("Arredondamento para cima de %d: %d\n", 5000, page_round_up(5000));

    int *p1 = (int *) kalloc(1);
    *p1 = 007;
    printf("Página 1: %p\n", p1);

    int *p2 = (int *) kalloc(2);
    printf("Página 2: %p\n", p2);//endereço do ponteiro

    char *p3 = (char *) kalloc(1);

    *p3 = 'U';
    *(p3 +1) = 'F';
    *(p3 +2) = 'M';
    *(p3 +3) = 'T';
    *(p3 +4) = '\0';
    printf("p3: %p, String: %s\n", p3, p3);
    //Tarefa
    //Fazer uma função que copia uma string para um endereço de memória
    //copia_string_end(char *str, void * end)
    //ex.: copia_string("xuxa o bet", p3);

    printf("Espaço entre página 1 e página 2:%d\n", (uint64) p2 - (uint64) p1);
    printf("Espaço entre página 1 e página 3:%d\n", (uint64) p3 - (uint64) p2);

}

void*
kalloc (int pages) { // Aloca quantidade de páginas
    uint8 *ptr; // ponteiro de página
    uint8 *fp_desc; // FIRST PAGE descritor de página
    int count; 
    if(pages == 0) return 0; // Nenhuma página é alocada

    for(int i = 0; i < total_pages; i++) { // percorre todas as páginas por um descritor de uma página livre
        ptr = (uint8*) HEAP_START + i;
        if(free_page(*ptr)) {
            if(count == 0) fp_desc = ptr;
            count++;
        } else {
            count = 0;
            fp_desc = 0;
        }

        if(count == pages) break;
    }
    // se não encontrar páginas livres
    if(count < pages) fp_desc = 0;
        if(fp_desc != 0) {
            //ENCONTRAMOS PÁGINAS LIVRES SOLICITADAS
            for(int i = 0; 1 < pages; i++) {
                set_free_page_flag(fp_desc + i, 0);
                set_last_page_flag(fp_desc + i, !LAST_PAGE);
            }
            // última página do bloco
            set_last_page_flag(fp_desc + pages - 1, LAST_PAGE);
            
            //Calcula endereço de retorno
            int pos_desc = (uint64) fp_desc - (uint64) HEAP_START; // encontrar a posição do descritor
            return (void*) (alloc_start + PAGE_SIZE *pos_desc); // ENDEREÇO DA PRIMEIRA PÁGINA DO BLOCO
        }
    return 0;
}
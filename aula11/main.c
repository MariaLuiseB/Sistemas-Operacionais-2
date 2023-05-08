// imprimir olá mundo 
#include "types.h"
#include "defs.h"
#include "console.h"


void entry() { // o boot salta para a função entry
    memory_init();
    //Inicializa os descritores da página
    pages_init();



}

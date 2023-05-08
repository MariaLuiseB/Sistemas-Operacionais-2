# inicializa o boot do S.O
.global _start

_start:
#obtém o id do hart (core) atual
csrr t0, mhartid   # t0 <- mhartid 
# bnez (branch if not equal to zero) se o conteúdo de t0 for 0(processador 0)
# salta para desativa 
bnez t0, desativa 
# só o hart 0 executa a partir daqui
la sp, stack_end # load address sp <- stack_end
# !!! saltar para a função principal em C
j entry # salta para entry no main.c

desativa: # desativa o processador 
    wfi # wait for interruption, espera outra chamada de sistema 
    #volta para o inicio do loop caso o processador seja ativado
    j desativa # laço para voltar a chamar desativa 

.skip 4096 # pula 4096 bytes (4KB)
stack_end: # fim da pilha


     
.global _start
 
_start: 
    csrr t0, mhartid  # 
    bnez t0, park  # salta se não igual a zero
    la sp, stack_end # carrega sp com endereço stack_end
    j entry # função em C
# Coloca os demais cores em espera
park:
    wfi     # espera por interrupção
    j park  # volta à espera
    
# .skip 4096 # pula 4096 bytes (4KB)
# stack_end: # fim da pilha

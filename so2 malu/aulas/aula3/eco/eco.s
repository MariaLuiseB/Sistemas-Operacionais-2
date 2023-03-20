# exercicio: digitar uma string e escrever na tela 
# chamar função read (0, , )
# chamar função write 
# chamar exit 
.section .text 
.global _start # importou e deixou o _start visivel para o linker
_start: # onde começa o programa (entry point)

#CHAMAR FUNCAO READ

# ler o que tá no espaço
li a7, 63 # carrega o que ta no registrador

# carrega argumentos para os reistradores
li a0, 0 # a0 <- 0 (entrada padrão DE LEITURA)

#carregar endereço da string
la a1, espaco 

# carregar quantidade de bytes da string
li a2, 20 

ecall 

#CHAMAR FUNCAO WRITE 
# 64: ID da chamada de sistema write
# li : load immediate (Carrega o numero)
li a7, 64 # a7 <- 64

# mover o que leu para outro registrador 
mv a4, a0

# carregar os argumentos para o registradores
li a0, 1 # a0 <- 1 ( 1 = saída padrão)

# carregar o endereço da string
#la : load adress
la a1, espaco 

# carregar quantidade de bytes da string
li a2, a4 # a2 <- 11 (qtde de bytes da string)

#chamar o sistema operacional
ecall 

#94: ID da chamada de sistema exit
li a7, 94 # a7 <- 94
li a0, 0
ecall

.section .data 
# diretiva que cria um espaço de memoria de bytes 
espaco: .byte 20 



    


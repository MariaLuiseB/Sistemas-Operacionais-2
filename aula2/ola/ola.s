#exercicio de printar ola mundo 
#invocar a funcao write com 3 parâmetros write (fd, char *s, qtde)

.global _start # importou e deixou o _start visivel para o linker 

_start: # onde começa o programa (entry point)

# 64: ID da chamada de sistema write
# li : load immediate (Carrega o numero)
li a7, 64 # a7 <- 64

# carregar os argumentos para o registradores
li a0, 1 # a0 <- 1 ( 1 = saída padrão)

# carregar o endereço da string
#la : load adress
la a1, msg 

# carregar quantidade de bytes da string
li a2, 11 # a2 <- 11 (qtde de bytes da string)

# chamar o sistema operacional
ecall

#94: ID da chamada de sistema exit
li a7, 94 # a7 <- 94
li a0, 0
ecall

# imprimir uma string olá mundo
msg: .string "ola mundo\n"

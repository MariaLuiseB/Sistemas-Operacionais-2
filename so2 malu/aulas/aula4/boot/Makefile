PRE = riscv64-linux-gnu-
CC = $(PRE)gcc
LD = $(PRE)ld
# Parâmetros para o compilador C
# CFLAGS += -ffreestanding # não há um SO no ambiente de execução
CFLAGS += -march=rv64gc  # arquitetura RISC-V de 64 bits
# tipos longos e ponteiros são de 64 bits. Inteiros são de 32 bits
CFLAGS += -mabi=lp64  
CFLAGS += -Wall # Mostra mais mensagens de warning
# CLFLAGS += -g  # Gera informações extra p/ depuração
CFLAGS += -O0 # Otimiza o código o mínimo possível
CFLAGS += -c  # compila mas não invoca o linker

#Parâmetros para o linker
LDFLAGS += -nostdlib  # Não vincula funções de terceiros (standard lib)
LDFLAGS += -Tkernel.ld # Script para o linker

# Emulador
QEMU = qemu-system-riscv64 
OBJ = boot.o main.o 

%.o: %.c 
	$(CC) $(CFLAGS) $<


%.o: %.s
	$(CC) $(CFLAGS) $<

kernel: $(OBJ)
	$(LD) $(LDFLAGS) -o kernel $(OBJ)

# main.o: main.c 
# 	$(CC) $(CFLAGS) main.c
# boot.o: boot.s 
# 	$(CC) $(CFLAGS) boot.s

run: kernel
	$(QEMU) -append 'console=ttyS0'  -nographic -serial mon:stdio -smp 4 -machine virt -bios none -kernel kernel


clean:
	rm -f boot.o main.o kernel
	
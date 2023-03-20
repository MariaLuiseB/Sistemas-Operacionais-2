#ola:	
#	@echo "Olá, mundo!"
#	@date
#	@touch ola 
#adeus:
#	@echo "Adeus!" > adeus
#clean:
#	@rm -f ola	
#	@echo "Arquivo ola removido"

#all: regra1, regra2, regra3
#	@echo "Todas as regras foram executadas!"

#regra1:
#	touch regra1
#regra2:
#	touch regra2
#regra3:
#	touch regra3

#clean:
#	rm -f regra1, regra2, regra3

##variáveis

GCC := riscv64-linux-gnu-gcc
QEMU := qemu-riscv64-static

all: r1 r2 
	echo "regra all executada"
r1, r2:
	echo "regra $@ executada"
	touch 

# Regra padrão: invoca o compilador para gerar o executável
ola: ola.o
	$(GCC) -static ola.o -o ola

# invoca o compilador para gerar o arquivo objeto
ola.o: ola.c
	$(GCC) -c ola.c -o ola.o

# gera o código fonte 
ola.c:
	echo "#include<stdio.h>" > ola.c 
	echo "int main(void) {" >> ola.c 
	echo "printf(\"Olá mundo!\");" >> ola.c 
	echo "}" >> ola.c 

#remove os três arquivos
clean:
	rm -f ola ola.c ola.o 

run:
	$(QEMU) ola 

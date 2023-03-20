GCC := riscv64-linux-gnu-gcc
AS := riscv64-linux-gnu-as
QEMU := qemu-riscv64-static 

somamain.x: soma.o somamain.o
	$(GCC) -static soma.o somamain.o -o somamain.x

soma.o: soma.s
	$(AS) -o soma.o soma.s

somamain.o: somamain.c
	$(GCC) -c somamain.c -o somamain.o

run: somamain.x
	$(QEMU) somamain.x

clean:
	rm -f  *.o *.x  


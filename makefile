fun1: program.o
	gcc -no-pie program.o
	./a.out

program.o: program.asm
	yasm program.asm -f elf64

clear:
	rm -f program.o program

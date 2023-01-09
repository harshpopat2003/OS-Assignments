all:
	@nasm -f elf64 assigment0.asm -o assigment0.o
	@gcc -no-pie assigment0.o
	@./a.out

clean:
	@rm -f assigment0.o
	@rm -f a.out
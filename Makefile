
asm_file:
	nasm -f elf64 -o build/bridge.o asm/bridge.asm

dump:
	objdump -d -M intel build/bridge.o

refresh: asm_file dump

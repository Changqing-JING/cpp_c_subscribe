
asm_file:
	nasm -f elf64 -o build/bridge.o asm/bridge.asm

asm_arm:
	aarch64-linux-gnu-gcc -c -o build/bridge_arm.o asm/bridge_arm.s

dump_x86:
	objdump -d -M intel build/bridge.o

dump_arm: asm_arm
	aarch64-linux-gnu-objdump -d build/bridge_arm.o

refresh: asm_file dump

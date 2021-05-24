sourceDir=./
buildDir=../build
asm_file:
	nasm -f elf64 -o ${buildDir}/bridge.o ${sourceDir}/bridge.asm

asm_arm:
	aarch64-linux-gnu-gcc -c -o ${buildDir}/bridge_arm.o ${sourceDir}/bridge_arm.s

dump_x86: asm_file
	objdump -d -M intel ${buildDir}/bridge.o

dump_arm: asm_arm
	aarch64-linux-gnu-objdump -d ${buildDir}/bridge_arm.o

refresh: asm_file dump

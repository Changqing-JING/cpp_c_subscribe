bridge:

load_abi:
mov rax, 0x1122334455667788
mov rdx, qword [rax]

mov r15, qword [rax + 8]

call rdx

ret
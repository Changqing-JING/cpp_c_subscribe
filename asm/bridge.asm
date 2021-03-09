bridge:
push rbx
push rsi

load_abi:
mov rax, 0x1122334455667788
mov rbx, qword [rax]

mov rsi, qword [rax + 8]

call rbx

pop rsi
pop rbx

ret
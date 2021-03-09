bridge:
push rbx
mov rax, 0x11223334455667788
mov rbx, qword [rax]

add rax, 8

mov rsi, qword [rax]

call rbx

pop rbx

ret
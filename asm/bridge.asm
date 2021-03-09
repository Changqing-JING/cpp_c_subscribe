bridge:
push rbx
mov rax, 0x11223334455667788
mov rbx, qword [rax]

mov rsi, qword [rax + 8]

call rbx

pop rbx

ret
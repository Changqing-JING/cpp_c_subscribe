bridge:
push rbx
push rsi

load_abi:
mov rax, 0x1122334455667788
mov rbx, qword [rax]

mov rsi, qword [rax + 8]
sub rsp, 8 ;16 bit align for macos

call rbx

add rsp, 8

pop rsi
pop rbx

ret
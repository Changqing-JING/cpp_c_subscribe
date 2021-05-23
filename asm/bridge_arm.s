	.arch armv8-a
	.file	"bridge_arm.asm"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	    mov     x0, 30600
        movk    x0, 0x5566, lsl 16
        movk    x0, 0x3344, lsl 32
        movk    x0, 0x1122, lsl 48
		ldr     x15, [x0, 8]
        ldr     x0, [x0]
        br      x0
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits

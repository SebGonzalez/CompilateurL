;./nasm/nasm -f macho -g test3.nasm -o test.o
;ld -arch i386 -macosx_version_min 10.7 -o test_exec test.o

%include 'io.asm'

section .bss
sinput:	resb	255	;
v$a: resd 1

section	.text
global start
start:
	call main
	mov	eax, 1		 ; 1 est le code de SYS_EXIT
	int 0x80
main:
	push 2
	pop eax
	mov [v$a], eax
	push 2
	pop eax
	call iprintLF
	ret


section .bss
v$a: resd 1
section .text
global _start
_start:
call main
mov rax, 60
syscall
main:
push 4
pop rax
mov [v$a], rax
push qword [v$a]
pop rax
ret
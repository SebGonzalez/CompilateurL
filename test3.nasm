%include 'io.asm'
section .bss
sinput: resb  255 ;
v$x: resd 1

section .text
global _start
_start :
call main
mov eax, 1
int 0x80
add :
push ebp
mov ebp, esp
sub esp, 4 ; allocation variable locale
push dword[ebp + 4 + 4*2 - 0]
push dword[ebp + 4 + 4*2 - 4]
pop ebx
pop eax
add eax, ebx
push eax
pop eax
mov [ebp-4-0], eax ;affectation dans une variable locale
push dword[ebp-4-0]
pop eax
call iprintLF
mov esp, ebp ;effacer variable locale
pop ebp ;retablir ancienne valeur ebp
ret
main :
push ebp
mov ebp, esp
sub esp, 4 ; allocation variable locale
sub esp, 4 ; allocation variable locale
sub esp, 4 ; allocation variable locale
push 5
pop eax
mov [v$x], eax ;affectatation dans une variable globale
push 7
pop eax
mov [ebp-4-4], eax ;affectation dans une variable locale
sub esp, 4 ;allocation valeur de retour
push dword[v$x]
push dword[ebp-4-4]
call add
add esp, 4*2; desallocation des arguments
pop eax
mov [ebp-4-8], eax ;affectation dans une variable locale
push dword[ebp-4-8]
pop eax
call iprintLF
mov esp, ebp ;effacer variable locale
pop ebp ;retablir ancienne valeur ebp
ret


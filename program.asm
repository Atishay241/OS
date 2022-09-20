section .data

msg db "Given Integer Input : ", 10, 0
msg1 db 10,"Give String input: : ", 10, 0

input1 db "%d", 0
input2 db "%s", 0

section .bss

int_inp resb 1
str_inp resb 25


section .text
global main
extern scanf
extern printf
default rel

main:
	push rbp
	lea rdi, [msg]
        xor rax, rax
	call printf


	lea rdi, [input1]
	lea rsi, [int_inp]
	xor rax, rax
	call scanf

	lea rdi, [input1]
	mov esi, [int_inp]
	xor rax, rax
	call printf

	lea rdi, [msg1]
	xor eax,eax
	call printf

	lea rdi, [input2]
	lea rsi, [str_inp]
	xor rax,rax
	call scanf

	mov rdi, input2
	mov esi, str_inp
	xor rax, rax
	call printf

	pop rbp
	mov rax, 0
	ret



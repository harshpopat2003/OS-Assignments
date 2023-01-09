section .data

int_start_msg:    db        "Enter an integer value: " , 10, 0 
int_end_msg:      db        "The integer value is: " , 10, 0
str_start_msg:    db        "Enter a string: " , 10, 0
str_end_msg:      db        "The string is: " , 10, 0
str_space:        db        " ", 10, 0
strFormat:        db        "%s", 0
intFormat         db        "%d", 0


section .bss
var1: resd  1
var2: resd  1


global main
extern printf
extern scanf
extern puts
extern exit
default rel

section .text

main: 

        push rbp ;setup stack

        ;printf("Enter an integer value: \n")
        lea rdi, [int_start_msg] 
        xor rax, rax
        call printf


        ;take input from the user
        ;scanf("%d", &var1);
        lea rdi, [intFormat]
        lea rsi, [var1]
        xor rax, rax
        call scanf

        ;printf("Enter a String:\n", var2)
        lea rdi, [str_start_msg] 
        xor rax, rax
        call printf

        ;take input from the user 
        ;scanf("%s", &var2);
        lea rdi, [strFormat]
        lea rsi, [var2]
        xor rax, rax
        call scanf

        ;printf("The integer value is: %d\n", var1)
        lea rdi, [int_end_msg]
        lea rsi, [var1]
        xor rax, rax
        call printf

        ;printing the value of var1
        lea rdi, [intFormat]
        mov esi, [var1]  
        xor rax, rax
        call printf

        ;printf("\n")
        lea rdi, [str_space]
        xor rax, rax
        call printf

        ;printf("The string is: %s\n", var2)
        lea rdi, [str_end_msg]
        lea rsi, [var2]
        xor rax, rax
        call printf

        ;printing the value of var2
        lea rdi, [strFormat]
        lea rsi, [var2]
        xor rax, rax
        call printf

        ;printf("\n");
        lea rdi, [str_space]
        xor rax, rax
        call printf

        ; return
        pop rbp ;restore stack
        mov rax, 0 ;normal exit
        ret
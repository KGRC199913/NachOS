# 1 "start.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "start.c"
# 10 "start.c"
# 1 "../userprog/syscall.h" 1
# 16 "../userprog/syscall.h"
# 1 "../threads/copyright.h" 1
# 17 "../userprog/syscall.h" 2
# 11 "start.c" 2

        .text
        .align 2
# 24 "start.c"
 .globl __start
 .ent __start
__start:
 jal main
 move $4,$0
 jal Exit
 .end __start
# 45 "start.c"
 .globl Halt
 .ent Halt
Halt:
 addiu $2,$0,0
 syscall
 j $31
 .end Halt

 .globl Exit
 .ent Exit
Exit:
 addiu $2,$0,1
 syscall
 j $31
 .end Exit

 .globl Exec
 .ent Exec
Exec:
 addiu $2,$0,2
 syscall
 j $31
 .end Exec

 .globl Join
 .ent Join
Join:
 addiu $2,$0,3
 syscall
 j $31
 .end Join

 .globl Create
 .ent Create
Create:
 addiu $2,$0,SC_Create
 syscall
 j $31
 .end Create

 .globl Open
 .ent Open
Open:
 addiu $2,$0,5
 syscall
 j $31
 .end Open

 .globl Read
 .ent Read
Read:
 addiu $2,$0,6
 syscall
 j $31
 .end Read

 .globl Write
 .ent Write
Write:
 addiu $2,$0,7
 syscall
 j $31
 .end Write

 .globl Close
 .ent Close
Close:
 addiu $2,$0,8
 syscall
 j $31
 .end Close

 .globl Fork
 .ent Fork
Fork:
 addiu $2,$0,9
 syscall
 j $31
 .end Fork

 .globl Yield
 .ent Yield
Yield:
 addiu $2,$0,10
 syscall
 j $31
 .end Yield

 .globl ReadInt
 .ent ReadInt
ReadInt:
 addiu $2,$0,11
 syscall
 j $31
 .end ReadInt

 .globl PrintInt
 .ent PrintInt
PrintInt:
 addiu $2,$0,12
 syscall
 j $31
 .end PrintInt

 .globl ReadChar
 .ent ReadChar
ReadChar:
 addiu $2,$0,13
 syscall
 j $31
 .end ReadChar

 .globl PrintChar
 .ent PrintChar
PrintChar:
 addiu $2,$0,14
 syscall
 j $31
 .end PrintChar

 .globl ReadString
 .ent ReadString
ReadString:
 addiu $2,$0,15
 syscall
 j $31
 .end ReadString

 .globl PrintString
 .ent PrintString
PrintString:
 addiu $2,$0,16
 syscall
 j $31
 .end PrintString

        .globl CreateFile
        .ent CreateFile
CreateFile:
 addiu $2, $0, 4
 syscall
 j $31
 .end CreateFile

        .globl Open
        .ent Open
Open:
        addiu $2, $0, 5
        syscall
        j $31
        .end Open

        .globl Close
 .ent Close
Close:
        addiu $2, $0, 8
        syscall
        j $31
        .end Close

 .globl Read
 .ent Read
Read:
 addiu $2, $0, 6
 syscall
 j $31
 .end Read

        .globl __main
        .ent __main
__main:
        j $31
        .end __main

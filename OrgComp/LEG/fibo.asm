.globl main
.text

main:

li $v0, 5
syscall

move $a0, $v0 # le o n de fib(n)

jal fibo
move $a0, $v0

li $v0, 1
syscall

li $v0, 10
syscall 

fibo:

subi $sp, $sp, 12
sw $a0, 0($sp)
sw $ra, 4($sp)

bne $a0, 1, notone
addi $sp, $sp, 12
li $v0, 0
jr $ra
notone:

bne $a0, 2, nottwo
addi $sp, $sp, 12
li $v0, 1
jr $ra
nottwo:

subi $a0, $a0, 1
jal fibo
move $t0, $v0
sw $t0, 8($sp)

lw $a0, 0($sp)
subi $a0, $a0, 2
jal fibo
move $t1, $v0
lw $t0, 8($sp)

add $v0, $t0, $t1


lw $ra, 4($sp)
addi $sp, $sp, 12
jr $ra



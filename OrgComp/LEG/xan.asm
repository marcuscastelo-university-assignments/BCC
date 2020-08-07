.globl main

.text
main:

li $v0, 5
syscall
move $a0, $v0

li $v0, 5
syscall

move $a1, $v0

li $v0, 1
jal elev

move $a0, $v0 #moves result of elev to print argument
li $v0, 1
syscall

li $v0, 10
syscall #exit

elev:

subi $sp, $sp, 8
sw $a1, 4($sp)
sw $ra, 0($sp)

slti $t0, $a1, 1
beq $t0, $zero, L1

addi $sp, $sp, 8
jr $ra

L1:

subi $a1, $a1, 1
jal elev

lw $a1, 4($sp)
lw $ra, 0($sp)
addi $sp, $sp, 8

mul $v0, $v0, $a0

jr $ra










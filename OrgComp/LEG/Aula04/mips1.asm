.globl main

.data
myflt:
.float 0.0
.text

main:
	li $v0, 6
	syscall
	mov.s $f1, $f0
	
	syscall
	mov.s $f2, $f0

	syscall
	mov.s $f3, $f0
	
	l.s $f4, 0
	
	add.s $f4, $f4, $f1
	add.s $f4, $f4, $f2
	add.s $f4, $f4, $f3
	
	l.s $f6, 3
	div.s $f5, $f4, $f6
	
	li $v0, 2
	mov.s $f12, $f5
	syscall
	
	
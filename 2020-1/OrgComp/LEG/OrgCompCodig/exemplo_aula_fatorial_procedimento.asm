	.data
	
	.text
	
	.globl main
	
main:

	li $a0, 6
	# parâmetro $a0
	# retorno $v0
	jal fatorial
	#j fatorial
#retorno: 

	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall


fatorial:
	# empilha os registradores
	
	
	#calcula o fatorial
	# em $v0 o retorno
	
	addi $v0, $zero, 1
	li $v0, 1	
	addi $t6, $zero, 1
	
loopfat:			# loop para o calculo do fatorial 
	beq $a0, $t6, endloop   # condicional que marca o inicio do while

	mul $v0, $v0, $a0	# fat = fat * cont
    addi $a0, $a0, -1	# cont--
   	j loopfat
	
	
endloop:
	#desempilha
	

	#retorno
	jr $ra





	.data
imp_rest:	.asciiz "O valor da soma eh "
	.text	
	.globl main
main:
	li $t1, 3
	li $t2, 4
	jal soma #Jump and Link, salva o endereço PC+4 (proxima instrucao) no registrador ra e vai para rotulo soma
	
	li $v0, 1
	move $a0, $t0
	syscall
	j fim #Jump, vai direto para o fim, pois senao irá executar o codigo da soma novamente
	
soma:
	add $t0, $t1, $t2 
	jr $ra #Jump Register, vai para o endereço indida no registrador (ra)
	
fim:
	li $v0, 10
	syscall

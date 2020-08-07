.data
	
dig:	.asciiz "\nDigite uma opção:\n\tPrf (Professor)\n\tAln (Aluno)\n" 
pos:	.space 4 #reservando 4 bytes na mem (4 caracteres ascii)
wlcp:	.asciiz "\nBem vindo Professor!\n"
wlca:	.asciiz "\nBem vindo Aluno!\n"
prof:	.asciiz "Prf\n"
alun:	.asciiz "Aln\n"

	.text
	.globl main
	
	#iniciamos o programa perguntando ao usuario
main:	li $v0, 4 # v0 = 4 => print string
	la $a0, dig #string a ser impressa eh passa no $a0
	syscall
	
	#leitura de uma string e armazenamento em um espaco de mem.
	li $v0, 8 # v0 = 8 => read string
	la $a0, pos # a0 = pos mem -> posicao de armazenadas na mem
	li $a1, 4 # a1 = qtd de bytes/caracteres a serem lidos 
		  #considerando sempre o \n (nr_caracteres - 1)
	syscall #resultado da leitura salva em $a0

	#imprimindo string (já em $a0)	
	li $v0, 4
	syscall 

vl_str:	la $t1, prof #colocando valores em reg. temporarios
	move $t2, $a0 #colocando valores em reg. temporarios
	jal comp_str_prof
	la $t1, alun
	move $t2, $a0
	jal comp_str_alun
	j fim

#para comparar uma string eh preciso comparar byte/caracter a byte/caracter
#como são apenas 3 caracteres vamos repetir um pouco de código, se fosse maior
#deveriamos fazer um loop
comp_str_prof:	lb $t3($t1) #carrega 1 byte da str1
		lb $t4($t2) #carrega 1 byte da str2
		bne $t3, $t4, dif #compara
		addi $t1, $t1, 1 #proxima posicao str1
		addi $t2, $t2, 1 #proxima posicao str2
		lb $t3($t1) #carrega 1 byte da str1
		lb $t4($t2) #carrega 1 byte da str2
		bne $t3, $t4, dif #compara
		addi $t1, $t1, 1 #proxima posicao str1
		addi $t2, $t2, 1 #proxima posicao str2
		lb $t3($t1) #carrega 1 byte da str1
		lb $t4($t2) #carrega 1 byte da str2
		bne $t3, $t4, dif #compara
		j go_prof #vai para o rotulo

#para comparar uma string eh preciso comparar byte/caracter a byte/caracter
#como são apenas 3 caracteres vamos repetir um pouco de código, se fosse maior
#deveriamos fazer um loop
comp_str_alun:	lb $t3($t1) #carrega 1 byte da str1
		lb $t4($t2) #carrega 1 byte da str2
		bne $t3, $t4, dif #compara
		addi $t1, $t1, 1 #proxima posicao str1
		addi $t2, $t2, 1 #proxima posicao str2
		lb $t3($t1) #carrega 1 byte da str1
		lb $t4($t2) #carrega 1 byte da str2
		bne $t3, $t4, dif #compara
		addi $t1, $t1, 1 #proxima posicao str1
		addi $t2, $t2, 1 #proxima posicao str2
		lb $t3($t1) #carrega 1 byte da str1
		lb $t4($t2) #carrega 1 byte da str2
		bne $t3, $t4, dif #compara
		j go_alun #vai para o rotulo

dif:	jr $ra #Jump Register $ra -> retorna pra quem realizou o jal

go_prof:	li $v0, 4 # v0 = 4 => print string
		la $a0, wlcp #string a ser impressa eh passa no $a0
		syscall
		j main
		
go_alun:	li $v0, 4 # v0 = 4 => print string
		la $a0, wlca #string a ser impressa eh passa no $a0
		syscall
		j main
	
fim:	li $v0, 10
	syscall

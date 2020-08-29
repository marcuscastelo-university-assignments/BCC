# exemplos de syscall

.data
strstring:  .asciiz "\n digite uma string de 10 caracteres " 
str: .asciiz "\n digite o valor " 
str2: .asciiz "\n a resposta = " 

pos:	.space 4 #reservando 4 bytes na mem (4 caracteres ascii)
.text
.globl main


main:
 	#imprimir string
 	li $v0, 4  
 	la $a0, str
 	syscall
 	
 	#ler uma string
 	li $v0, 8
 	#uso do la devido a leitura da posição da memoria
 	la $a0, pos # a0 = pos mem -> posicao de armazenadas na mem
	li $a1, 4 # a1 = qtd de bytes/caracteres a serem lidos 
		  #considerando sempre o \n (nr_caracteres - 1)
 	syscall
 	
 	#imprimindo string (já em $a0)	
	li $v0, 4
	syscall 
	
	#uso do move para moveer valores entre dois registradores
	move $t2, $a0 #colocando valores em reg. temporarios
	
	#imprimindo string 
	move $a0, $t2 #colocando valores no argumento
	li $v0, 4
	syscall 
	
	

       

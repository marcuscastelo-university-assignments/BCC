	.data
str:	.asciiz "the answer = "
	.text
	
        li $v0, 4 #c�digo de chamada ao sistema para print_str
	la $a0, str #endere�o da string a imprimir
	syscall #imprime a string
	
	li $v0, 1 #c�digo de chamada ao sistema para print_int
	li $a0, 5 #inteiro a imprimir
	syscall #imprime
	 

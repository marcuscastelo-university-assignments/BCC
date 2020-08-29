	.data
str:	.asciiz "the answer = "
	.text
	
        li $v0, 4 #código de chamada ao sistema para print_str
	la $a0, str #endereço da string a imprimir
	syscall #imprime a string
	
	li $v0, 1 #código de chamada ao sistema para print_int
	li $a0, 5 #inteiro a imprimir
	syscall #imprime
	 

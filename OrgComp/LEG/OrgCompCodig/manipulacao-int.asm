### Programa Assembly MIPS para somar dois número inteiros e ...
## imprimir o resultado ###
	.data
	# inicia segmento de dados
str_dig: .asciiz "Digite um numero: " # definindo a string str_dig
str_res: .asciiz "Resultado: " # definindo a string str_res

	.text 		# diretiva p/ início do segmento de texto
	.globl main	# diretiva p/ usar rotulo em outro prog.

main: # rótulo para ponto de entrada no processo

	# load immediate
	li $v0, 4	# atribui 4 para $v0. Codigo para print_str
	# load address
	la $a0, str_dig	# carrega endereco de str_dig em $a0
			# eh o end da string a ser impressa
	syscall		# chamada de sistema para E/S
	
	# vai ler um inteiro vindo do teclado
	li $v0, 5			# atribui 5 para $vo. Codigo para read_int
	syscall				# chamada de sistema para E/S. Retorno estara em $v0
	move $t1, $v0		# copia conteudo digitado para $t1 para preservar dado
	

	# load immediate
	li $v0, 4	# atribui 4 para $v0. Codigo para print_str
	# load address
	la $a0, str_dig	# carrega endereco de str_dig em $a0
			# eh o end da string a ser impressa
	syscall		# chamada de sistema para E/S
	
	# vai ler um inteiro vindo do teclado
	li $v0, 5			# atribui 5 para $vo. Codigo para read_int
	syscall				# chamada de sistema para E/S. Retorno estara em $v0
	move $t2, $v0		# copia conteudo digitado para $t2 para preservar dado
	
	#soma
	add $t3, $t1, $t2 # soma o valor de $t1 + $t2 e armazena em $t3
	
	# load immediate
	li $v0, 4	# atribui 4 para $v0. Codigo para print_str
	# load address
	la $a0, str_res	# carrega endereco de str_res em $a0
			# eh o end da string a ser impressa
	syscall		# chamada de sistema para E/S
	
	li $v0, 1	# atribui 1 para $v0. Codigo para print_int
	move $a0, $t3	# copia nr a ser impresso para $a0.
			# argumento de entrada para a impressao do int
	syscall		# chamada de sistema para E/S

	#realizar o exit	
	li $v0, 10			# atribui 10 para $v0. Codigo para exit (termina programa)
	syscall				# chamada de sistema para E/S

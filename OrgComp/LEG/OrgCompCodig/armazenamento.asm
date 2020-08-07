	.data
var1:	.word	9 # declara var1 na memoria; e armazena o valor 9
nl:	.asciiz "\n"
	.text
	
inicio:	lw	$t0, var1 # carrega o valor da RAM em var1 no $t0: $t0 = var1
	li	$t1, 7    #  $t1 = 7  "load immediate"
	add	$t1, $t1, $t0 # soma t1 = t1+t0
	sw	$t1, var1 # armazena o conteudo de $t1 na RAM em var1: var1 = $t1
	
	#Imprime a soma
	li $v0, 1	# atribui 1 para $v0. Codigo para print_int
	move $a0, $t1	# copia nr a ser impresso para $a0.
			# argumento de entrada para a impressao do int
	syscall		# chamada de sistema para E/S
	
	# Imprime pular linha
	li $v0, 4	# atribui 4 para $v0. Codigo para print_str
	la $a0, nl	# (load address) carrega endereco de nl em $a0
	syscall		# chamada de sistema para E/S
	
######### Outra forma de armazenar sem rotulos ############
	addi	$t1, $t1, 5 #soma imediata: $t1 = $t1 + 5
	li	$t2, 0x10010020 #carrega imediatamente um endereço para o registrador t2
	sw	$t1, 4($t2) #armazena nova soma ($t1) no END(t2) + 4bytes (32 bits/ prox endereco - word)
	lw	$t3, 4($t2) #recupara o valor de END(t2) + 4bytes e carrega em $t3
	
	#Imprime a NOVA soma
	li $v0, 1	# atribui 1 para $v0. Codigo para print_int
	move $a0, $t3	# copia nr a ser impresso para $a0.
			# argumento de entrada para a impressao do int
	syscall		# chamada de sistema para E/S
	
	# Imprime pular linha
	li $v0, 4	# atribui 4 para $v0. Codigo para print_str
	la $a0, nl	# (load address) carrega endereco de nl em $a0
	syscall		# chamada de sistema para E/S
	
######### Outra forma de armazenar com $gp ############
	sw $t3, 4($gp)
	lw $t4, 4($gp)
	
	#Imprime
	li $v0, 1	# atribui 1 para $v0. Codigo para print_int
	move $a0, $t4	# copia nr a ser impresso para $a0.
			# argumento de entrada para a impressao do int
	syscall		# chamada de sistema para E/S
	
######### Outra forma de armazenar com pilha ($sp e $fp) ############
push:  addi $sp, $sp, -4  # Decrementa o stack pointer por 4
       sw   $t4, 0($sp)   # salva $t4 para o stack pointer
       
pop:  lw   $t4, 0($sp)   # Carrega do stack para o $t4
      addi $sp, $sp, 4   # Incrementa o stack pointer por 4 (proxima posicao)
      
    #Imprime
       li $v0, 1	# atribui 1 para $v0. Codigo para print_int
       move $a0, $t4	# copia nr a ser impresso para $a0.
			# argumento de entrada para a impressao do int
       syscall		# chamada de sistema para E/S
	
fim:	li $v0, 10 #carrega o valor 10 (exit) em $v0
	syscall	   #executa a syscall para finalizar (exit) o programa

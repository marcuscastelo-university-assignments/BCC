.data
mainMenu:	.asciiz		"\nMenu Principal:\n(C) - Calcular\n(M) - Acessar Memoria\nSua escolha: "
memoryMenu:	.asciiz		"\nAcessar Memoria:\n(1) - Memoria 1\n(2) - Memoria 2\n(3) - Memoria 3\nSua escolha: "

calculoOpt:	.asciiz		"C\n"
memoriaOpt:	.asciiz		"M\n"

ln:		.asciiz		"\n"

mainMenuOption:	.space		0
menuIntResult:	.word		0
M1:		.word		0
M2:		.word		0
M3:		.word		0

debug:		.asciiz		"debug"

.text
main:
	# mostra o menu principal
	la $a0, mainMenu
	jal print_string

	# le a opcao do menu principal
	la $a0, mainMenuOption
	li $a1, 3
	jal read_string
	
	# faz a escolha do menu principal
	jal parse_mainMenuOption
	
	# compara o resultado da escolha do usuario
	calc_parseOpt:
		sw $v0, menuIntResult	
		lw $t0, menuIntResult

		beq $t0, 1, calc
		beq $t0, 2, memory
	end_calc:
	
	j end_program	

	
# Funcao da Calculadora
calc:
	la $a0, calculoOpt
	jal print_string
	j main
	

# Funcao de acessar memoria
memory:
	la $a0, memoryMenu
	jal print_string
	jal read_int
	
	read_M1:
		bne $v0, 1, read_M2
		lw $a0, M1
		jal print_int
		
		j end_memoryFunc
	
	read_M2:
		bne $v0, 2, read_M3
		lw $a0, M2
		jal print_int
		
		j end_memoryFunc
	
	read_M3:
		bne $v0, 2, end_memoryFunc
		lw $a0, M3
		jal print_int
		
		j end_memoryFunc
		
	end_memoryFunc:
	la $a0, ln
	jal print_string
	j main


#############FUNCOES ACESSIORIOS#############

# Funcao para finalizar o programa
end_program:
	li $v0, 10
	syscall


# Funcao de retorno
return:
	jr $ra


# Compara Strings
str_cmp:
	li $t2, 0
	move $t1, $a1
	move $t0, $a0
	
	loop:
		beq $t2, $a2, end_loop_equal
		lb $t3($t0)
		lb $t4($t1)
		
		bne $t4, $t3, end_loop_notEqual
		
		addi $t0, $t0, 1
		addi $t1, $t1, 1
		addi $t2, $t2, 1
		j loop
		
	end_loop_equal:
		li $v0, 1
		j end
		
	end_loop_notEqual:
		li $v0, 0
		j end
		
	end:
	jr $ra
	

# Funcao para printar string
print_string:
	li $v0, 4
	syscall
	j return


# Funcao para printar um inteiro
print_int:
	li $v0, 1
	syscall
	j return


# Funcao para ler string
read_string:
	li $v0, 8
	syscall
	j return


# Funcao para ler um inteiro
read_int:
	li $v0, 5
	syscall
	j return

	
# Funcao para avaliar o resultado do menu principal
parse_mainMenuOption:
	move $s0, $ra
	
	li $a3, 0
	la $a2, 2
	
	#verifica se o usuario escolheu a opcao de calcular
	la $a1, calculoOpt
	li $v0, 0
	jal str_cmp	
	if:
		beq $v0, 0, fi
		li $a3, 1
		j end_parseMenu
	fi:
		
	#verifica se o usuario escolheu a opcao de memoria
	la $a1, memoriaOpt
	li $v0, 0
	jal str_cmp
	if2:
		beq $v0, 0, fi2
		li $a3, 2
		j end_parseMenu
	fi2:
	
	
	end_parseMenu:
	move $v0, $a3
	move $ra, $s0
	j return
	
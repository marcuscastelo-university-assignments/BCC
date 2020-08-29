	.data		# inicia o segmento de dados

	#alinhamento automatico
	
	.word 0x12345678 #criando um palavra word = 1 byte = 8 bits
	.half 9876	#criando meia palavra: half-word = 4 bits

	.align 0	# determina o alinhamento dos bytes (2 elevado a 0)
	.half 1000	#criando meia palavra: half-word = 4 bits
str:	.byte  73, 70, 70, 0
	.byte  66, 67, 0
	.align 2	# determina alinhamento de 2 elevado a 2, ou seja, 4 bytes
	
	.text		# inicia o segmento de texto
	.globl main	# determina que o identificador main é global

main:
	li $v0, 4
	la $a0, str
	syscall
	
fim:	
	li $v0, 10
	syscall


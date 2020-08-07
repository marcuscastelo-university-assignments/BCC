	.data

dig:	.asciiz "\nDigite uma opção:\n\tP (Professor)\n\tA (Aluno)\n" 
wlcp:	.asciiz "\nBem vindo Professor!\n"
wlca:	.asciiz "\nBem vindo Aluno!\n"

	.text
	.globl main
	
	#iniciamos o programa perguntando ao usuario
main:	li $v0, 4 # v0 = 4 => print string
	la $a0, dig #string a ser impressa eh passa no $a0
	syscall
	

	#read char (ler apenas uma posicao, um caracter)
rd_chr: li $v0, 12 # v0 = 12 => read char
	syscall # resuldado da leitura salvo no $v0

	#imprindo char digitado pelo usuario
	move $a0, $v0	
	li $v0, 11
	syscall 

#Podemos comparar o valor de $v0 com algum caracter
vl_chr:	beq $a0, 'P', go_prof
	beq $a0, 'A', go_alun
	j fim

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

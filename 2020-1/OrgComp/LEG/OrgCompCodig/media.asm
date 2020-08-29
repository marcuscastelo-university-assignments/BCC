		.data
dig_qtd:	.asciiz "Digite a quantidade de notas:"
dig_nta:	.asciiz "Digite uma nota"
nota_rest:	.asciiz "A media eh: "

		.text
		.globl main

main:
		#pergunta a qtd de notas (N)
		li $v0, 4
		la $a0, dig_qtd
		syscall
		
		#ler a qtd de notas (N)-> $t0
		li $v0, 5
		syscall
		move $t0, $v0

		#verifica se usuario digitou a 
		#qtd de notas = 0, se sim volta
		#para o comeco
		beq $t0, $zero, main
		#ou vai pro fim -> beq $t0, $zero, fim

		#carregar zero no $t2
		li $t2, 0
		
		#registrado para salvar a qtd de notas
		move $t3, $t0
		
		#for
loop:		beq $t0, $zero, calc
		#Inicio do loop
		
		#peco pro usuario digita a nota
		li $v0, 4
		la $a0, dig_nta
		syscall
		
		#ler a nota digita pelo usuario
		li $v0, 5
		syscall
		move $t1, $v0
		
		#Somatoria salva em $t2
		add $t2, $t2, $t1
		
		#decrementando $t0
		subi $t0,$t0, 1
		
		#Fim do loop
		j loop
calc:
		#calcular media
		div $t4, $t2, $t3
		
		#exibir resultado (string)
		li $v0, 4
		la $a0, nota_rest
		syscall
		
		#exibir resultado (numero)
		li $v0, 1
		move $a0, $t4
		syscall

fim:		li $v0, 10
		syscall

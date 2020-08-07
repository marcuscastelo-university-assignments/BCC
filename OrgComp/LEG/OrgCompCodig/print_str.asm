.data	# diretiva p/ início do seg de dados
string:		.asciiz "Organização de Computadores"

.text 		# diretiva p/ início do segmento de texto
.globl main	# diretiva p/ usar rotulo em outro prog.
main:		# rótulo para ponto de entrada no processo

li $v0, 4	# $v0 = 4 cód. para print_str
la $a0, string	# $a0 = endereco da string
syscall		# chamada de sistema


li $v0, 10	# $ v0 = 10 cód para exit
syscall		# chamada de sistema. Fim do prog.


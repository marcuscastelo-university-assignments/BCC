.data	# diretiva p/ in�cio do seg de dados
string:		.asciiz "Organiza��o de Computadores"

.text 		# diretiva p/ in�cio do segmento de texto
.globl main	# diretiva p/ usar rotulo em outro prog.
main:		# r�tulo para ponto de entrada no processo

li $v0, 4	# $v0 = 4 c�d. para print_str
la $a0, string	# $a0 = endereco da string
syscall		# chamada de sistema


li $v0, 10	# $ v0 = 10 c�d para exit
syscall		# chamada de sistema. Fim do prog.


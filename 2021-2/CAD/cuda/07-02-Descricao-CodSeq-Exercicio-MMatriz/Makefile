all: prog-par prog-seq

run-par: prog-par
	./prog-par < entrada0.txt

run-seq: prog-seq
	./prog-seq < entrada0.txt

prog-par: 07-mult-mat-par.cu
	nvcc 07-mult-mat-par.cu -o prog-par

prog-seq: 07-mult-mat-seq.c
	gcc 07-mult-mat-seq.c -o prog-seq

example: example.cu
	nvcc example.cu -o example

zip:
	zip -r 07-mult-mat.zip *.cu *.txt Makefile *.py *.pdf *.c *.h
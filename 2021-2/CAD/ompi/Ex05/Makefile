all:
	@mpicc main.c -o programa -fopenmp -Wall
run:
	@mpirun -np 3 --oversubscribe programa
clean:
	@rm -f programa
zip:
	@zip -r Ex05.zip *.c *.h Makefile

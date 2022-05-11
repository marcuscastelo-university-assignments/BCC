all: master slave

run: master slave
	mpirun -np 4 --oversubscribe ./master 

master: 01-mmatrix-master.c
	mpicc -o master 01-mmatrix-master.c -lm

slave: 01-mmatrix-slave.c
	mpicc -o slave 01-mmatrix-slave.c -lm


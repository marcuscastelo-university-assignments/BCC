all: main
	rm *.o

run: main
	rm *.o
	./main

zip:
	zip Ex02.zip *.c *.h Makefile

OBJS = main.o graph.o list.o
main: $(OBJS)
	gcc $(OBJS) -o main -Wall
.c.o:
	gcc -c $< -o $@
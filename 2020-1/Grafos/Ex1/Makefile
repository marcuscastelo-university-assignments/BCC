all: main
	rm *.o

run: main
	rm *.o
	./main

zip:
	zip Ex01.zip *.c *.h Makefile

OBJS = main.o graph.o
main: $(OBJS)
	gcc $(OBJS) -o main
.c.o:
	gcc -c $< -o $@
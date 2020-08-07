OBJS = main.o list.o priority_queue.o graph.o edge.o

all: $(OBJS)
	gcc $(OBJS) -o main -Wall -lm

run: all
	./main

.c.o: 
	gcc -c $< -o $@

zip:
	zip AT4.zip *.c *.h Makefile
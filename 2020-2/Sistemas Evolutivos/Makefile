run: seEx1
	./seEx1

OBJS=graphing.o

all: $(OBJS)
	g++ main.cpp $(OBJS) -o seEx1 -lglut -lGL -lGLU -lm

.c.o:
	g++ -c $< -o $@ -Wall

seEx1: all
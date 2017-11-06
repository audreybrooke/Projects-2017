all: hw6

hw6: main.cpp functor.o
	g++ -g -Wall functor.o main.cpp -o main

functor.o: functor.cpp functor.h
	g++ -g -Wall -c functor.cpp -o functor.o

clean:
	rm -f functor.o
	rm -f main
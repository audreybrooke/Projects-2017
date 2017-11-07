all: learning

hw6q2: main.cpp functor.o
	g++ -g -Wall functor.o main.cpp -o main

learning: learning.cpp
	g++ -g -Wall learning.cpp -o learning

functor.o: functor.cpp functor.h
	g++ -g -Wall -c functor.cpp -o functor.o



clean:
	rm -f functor.o
	rm -f main
	rm -f learning
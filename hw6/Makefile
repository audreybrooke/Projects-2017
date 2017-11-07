all: hw6q2

learning: hw6q3

hw6q2: main.cpp functor.o
	g++ -g -Wall functor.o main.cpp -o main

hw6q3: learning.cpp
	g++ -g -Wall learning.cpp -o learning

functor.o: functor.cpp functor.h
	g++ -g -Wall -c functor.cpp -o functor.o

learning.o: learning.cpp learning.h
	g++ -g -Wall -c learning.cpp -o learning.o

clean:
	rm -f functor.o
	rm -f main
	rm -f learning
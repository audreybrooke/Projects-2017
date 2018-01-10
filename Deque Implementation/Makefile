all: DistanceCounter

DistanceCounter: DistanceCounter.cpp LLDeque.o
	g++ -g -Wall LLDeque.o DistanceCounter.cpp -o DistanceCounter

LLDeque.o: LLDeque.cpp LLDeque.h
	g++ -g -Wall -c LLDeque.cpp -o LLDeque.o

clean:
	rm -f LLDeque.o
	rm -f DistanceCounter

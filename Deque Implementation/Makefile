all: hw3q5

hw3q5: hw3q5.cpp LLDeque.o
	g++ -g -Wall LLDeque.o hw3q5.cpp -o hw3q5

LLDeque.o: LLDeque.cpp LLDeque.h
	g++ -g -Wall -c LLDeque.cpp -o LLDeque.o

clean:
	rm -f LLDeque.o
	rm -f hw3q5

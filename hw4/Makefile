all: hw4

hw4: hw4.cpp ArithmeticExpression.o
	g++ -g -Wall ArithmeticExpression.o hw4.cpp -o hw4

ArithmeticExpression.o: ArithmeticExpression.cpp ArithmeticExpression.h
	g++ -g -Wall -c ArithmeticExpression.cpp -o ArithmeticExpression.o

clean:
	rm -f ArithmeticExpression.o
	rm -f hw4






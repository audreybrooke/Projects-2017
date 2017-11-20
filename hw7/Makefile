all: hw7q2 hw7q3

hw7q2: hw7q2.cpp ArithmeticExpression.o BooleanExpression.o Command.o RecursiveParser.o
	g++ -g -Wall -std=c++11 ArithmeticExpression.o BooleanExpression.o Command.o RecursiveParser.o Variable.o hw7q2.cpp -o hw7q2

hw7q3: hw7q3.cpp ArithmeticExpression.o BooleanExpression.o Command.o RecursiveParser.o
	g++ -g -Wall -std=c++11 ArithmeticExpression.o BooleanExpression.o Command.o RecursiveParser.o Variable.o hw7q3.cpp -o hw7q3

clean:
	rm -f hw7q3
	rm -f hw7q2

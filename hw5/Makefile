all: hw5

hw5: hw5.cpp ArithmeticExpression.o BooleanExpression.o Command.o LineNumber.o
	g++ -g -Wall ArithmeticExpression.o BooleanExpression.o Command.o LineNumber.o hw5.cpp -o hw5

ArithmeticExpression.o: ArithmeticExpression.cpp ArithmeticExpression.h
	g++ -g -Wall -c ArithmeticExpression.cpp -o ArithmeticExpression.o

BooleanExpression.o: BooleanExpression.cpp BooleanExpression.h
	g++ -g -Wall -c BooleanExpression.cpp -o BooleanExpression.o

Command.o: Command.cpp Command.h
	g++ -g -Wall -c Command.cpp -o Command.o

LineNumber.o: LineNumber.cpp LineNumber.h
	g++ -g -Wall -c LineNumber.cpp -o LineNumber.o

clean:
	rm -f ArithmeticExpression.o
	rm -f BooleanExpression.o
	rm -f Command.o
	rm -f LineNumber.o
	rm -f hw5






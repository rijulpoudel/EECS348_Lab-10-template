all: calculator

calculator: main.o calculator.o
	g++ -std=c++11 -o calculator main.o calculator.o

main.o: main.cpp calculator.h
	g++ -std=c++11 -c main.cpp

calculator.o: calculator.cpp calculator.h
	g++ -std=c++11 -c calculator.cpp

clean:
	rm -f *.o calculator

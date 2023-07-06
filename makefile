all: main.o node.o
	g++ -g main.o node.o -o main

main.o: main.cpp node.cpp node.h
	g++ -c main.cpp

node.o: node.cpp node.h
	g++ -c node.cpp

clean:
	rm *.o
	rm main

run: all main
	./main

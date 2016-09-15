#Use this file to make the compiling faster
FLAGS = -Wall -std=c++11

main: main.cpp heap.cpp
	g++ $(FLAGS) -o main main.cpp heap.cpp

#heap.o: heap.cpp
#	g++ $(FLAGS) -c heap.cpp

#utils.o: utils.cpp
#	g++ $(FLAGS) -c utils.cpp

#program.o: program.h
#	gcc $(FLAGS) -c program.h

clean:
	rm *.o

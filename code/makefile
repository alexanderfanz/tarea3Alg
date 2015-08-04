
#CC=g++ -std=c++11
CC=g++ -fopenmp

CFLAGS=-c -Wall

all: project
	
project: main.o grid.o
	$(CC) main.o grid.o -o project
	
main.o: main.cpp grid.o
	$(CC) $(CFLAGS) main.cpp
	
grid.o: grid/grid.cpp grid/grid.h
	$(CC) $(CFLAGS) grid/grid.cpp -o grid.o

clean:
	rm *o project 

#all: hello

#hello: main.o factorial.o hello.o
#    g++ main.o factorial.o hello.o -o hello
#
#main.o: main.cpp
#    g++ -c main.cpp
#
#factorial.o: factorial.cpp
#    g++ -c factorial.cpp
#
#hello.o: hello.cpp
#    g++ -c hello.cpp
#
#clean:
#    rm *o hello
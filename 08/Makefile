CC = g++
FLAGS = -std=c++17 -pthread
all: main clean
main: main.o
	$(CC) main.o -o a.out
main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp
test: test.o
	$(CC) $(FLAGS) test.o -o test
	./test
	rm -f *.o
test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp
clean:
	rm -f *.o
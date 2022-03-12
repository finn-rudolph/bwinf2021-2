CPP = clang++
CFLAGS = -Wall -g -O3

all: 
	$(CPP) $(CFLAGS) k_xor.hpp io.hpp main.cpp -c
	$(CPP) $(CFLAGS) main.o -o main

test: test.cpp test.hpp
	$(CPP) $(CFLAGS) test.cpp -c
	$(CPP) $(CFLAGS) test.o -o test

clean:
	rm *.o *.gch
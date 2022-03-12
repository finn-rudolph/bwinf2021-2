CPP = clang++
CFLAGS = -Wall -g -O3

all:
	$(CPP) $(CFLAGS) k_xor.hpp io.hpp main.cpp -c
	$(CPP) $(CFLAGS) main.o -o main

test: all
	$(CPP) $(CFLAGS) test.cpp test.hpp -c
	$(CPP) $(CFLAGS) test.o -o test

clean:
	rm *.o *.gch
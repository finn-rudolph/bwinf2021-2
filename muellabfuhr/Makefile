CPP = g++
CFLAGS = -Wall -g -O2
BINS = main.o chinese_postman.o perfect_matching.o

all: $(BINS)
	$(CPP) $(CFLAGS) $(BINS) -o main

%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $^

clean:
	rm *.o *.gch
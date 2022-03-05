CPP = clang++
CFLAGS = -Wall -g
BINS = main.o io.o chinese_postman.o perfect_matching.o fhk_algorithm.o

all: $(BINS)
	$(CPP) $(CFLAGS) $(BINS) -o main

%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $^

clean:
	rm *.o *.gch
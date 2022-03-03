CPP = g++
CFLAGS = -Wall -g
BINS = main.o

all: $(BINS)
	$(CPP) $(CFLAGS) $(BINS) -o main

%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $^

clean:
	rm *.o *.gch
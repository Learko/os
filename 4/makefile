CXX = g++
CXXFLAGS = -std=c++14 -w -fpermissive
LDFLAGS = -pthread

all: main


main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

main: main.o
	$(CXX) main.o $(LDFLAGS) -o main


clean:
	rm *.o

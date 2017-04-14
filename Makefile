CC=g++
CFLAGS=-g -std=c++11
EXE=setDS


all: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXE)
run:
	./$(EXE)
clean:
	rm $(EXE)

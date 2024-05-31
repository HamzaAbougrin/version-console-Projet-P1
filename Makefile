CC=g++
CFLAGS=-Wall -std=c++11
SOURCES=src/main.cpp
EXECUTABLE=scheduler

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) 

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

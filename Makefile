CC = g++
CFLAGS = -c -g -Wall
DEPS = avl.h 2-5.h
LDFLAGS = 
SOURCES = main.cpp avl.cpp 2-5.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -lstdc++fs -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) *.cpp

clean:
	rm $(EXECUTABLE) $(OBJECTS)


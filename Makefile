CC=g++
IDIR =include/
#-fsanitize=address erg handige bug detectie tool: kan buffer overflows detecteren en memleaks
CCFLAGS= -Wall -std=c++11 -g -fsanitize=address -I$(IDIR)
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -g -fsanitize=address
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=bin/spel

all: $(TARGET)

$(TARGET): $(OBJECTS)
				$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h
				$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
				$(CC) $(CCFLAGS) -c $<

clean:
				rm -f *.o $(TARGET)

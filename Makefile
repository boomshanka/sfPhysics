DEBUGFLAGS = -g -DDEBUG

CC=colorgcc
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
SOURCE= src/*.cpp
CFLAGS=

RM=rm

BIN=physic

all: src/*.cpp src/*.hpp
	$(CC) $(SOURCE) -o $(BIN) $(CFLAGS) $(LIBS) 

debug: src/*.cpp src/*.hpp
	$(CC) $(SOURCE) $(DEBUGFLAGS) -o $(BIN) $(CFLAGS) $(LIBS) 

chaos:
	

clean:
	$(RM) $(BIN)


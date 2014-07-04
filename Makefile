CC = g++
D_BIN = dist
D_SRC = src
LIBFLAGS = -L C:\\MinGW\\lib -lopengl32 -lglu32 -lglew32 -lfreeglut
CFLAGS = -g -v -Wall -Wextra -I C:\\MinGW\\include -static-libgcc -static-libstdc++

all:
	g++ main.cpp util.cpp -g -Wall -o lab -lglut -lGL -lGLU -lGLEW

clean:
	rm -rf *.o $(D_BIN)/lab

win: main.o util.o Geometry.o
	$(CC) main.o util.o Geometry.o -o $(D_BIN)/lab $(CFLAGS) $(LIBFLAGS)

Geometry.o: $(D_SRC)/Geometry.cpp
	$(CC) -c $(D_SRC)/Geometry.cpp
	
main.o:
	$(CC) -c $(D_SRC)/main.cpp

util.o:
	$(CC) -c $(D_SRC)/util.cpp

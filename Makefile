CC=g++
LIBFLAGS=-L C:\\MinGW\\lib -lopengl32 -lglu32 -lglew32s -lfreeglut
FLAGS=-I C:\\MinGW\\include

all:
	g++  main.cpp util.cpp -g -Wall -o lab -lglut -lGL -lGLU -lGLEW

clean:
	rm -rf *.o lab

win:
	$(CC) -o lab -g -Wall main.cpp util.cpp $(FLAGS) $(LIBFLAGS)

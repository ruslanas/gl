MAIN = lab
SRC = main.cpp util.cpp Geometry.cpp

CC = g++
D_BIN = dist
D_SRC = src
D_OBJ = obj
LIBFLAGS = -L C:\\MinGW\\lib -lopengl32 -lglu32 -lglew32 -lfreeglut
INCLUDES = -I C:\\MinGW\\include
CFLAGS = -g -Wall -Wextra -static-libgcc -static-libstdc++

OBJ := $(SRC:.cpp=.o)
OBJ := $(addprefix $(D_OBJ)/, $(OBJ))
SRC := $(addprefix $(D_SRC)/, $(SRC))

win: $(MAIN)
	
$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(D_BIN)/$(MAIN) $(LIBFLAGS)

# existing auto generation techniques are not elegant enough
obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/main.cpp -o obj/main.o
obj/util.o: src/util.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/util.cpp -o obj/util.o
obj/Geometry.o: src/Geometry.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Geometry.cpp -o obj/Geometry.o

all:
	g++ main.cpp util.cpp -g -Wall -o lab -lglut -lGL -lGLU -lGLEW

clean:
	rm -rf *.o *~ $(D_BIN)/$(MAIN)


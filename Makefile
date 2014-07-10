MAIN = lab
SRC = main.cpp Geometry.cpp Vec3.cpp Matrix4.cpp UniformBlock.cpp \
Mesh.cpp Box.cpp Scene.cpp Application.cpp

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
obj/Geometry.o: src/Geometry.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Geometry.cpp -o obj/Geometry.o
obj/Vec3.o: src/Vec3.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Vec3.cpp -o obj/Vec3.o
obj/Matrix4.o: src/Matrix4.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Matrix4.cpp -o obj/Matrix4.o
obj/UniformBlock.o: src/UniformBlock.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/UniformBlock.cpp -o obj/UniformBlock.o
obj/Mesh.o: src/Mesh.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Mesh.cpp -o obj/Mesh.o
obj/Box.o: src/Box.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Box.cpp -o obj/Box.o
obj/Scene.o: src/Scene.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Scene.cpp -o obj/Scene.o
obj/Application.o: src/Application.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c src/Application.cpp -o obj/Application.o
	
all:
	g++ main.cpp util.cpp -g -Wall -o lab -lglut -lGL -lGLU -lGLEW

clean:
	rm -rf $(D_OBJ)/*.o *~ $(D_BIN)/$(MAIN)


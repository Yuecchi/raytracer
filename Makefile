CC		= g++
C_FILES = $(wildcard src/*.cpp)
O_FILES = $(C_FILES:src/%.cpp=build/%.o)
OUT		= bin/raytracer.exe
INCLUDE = -I include/
LIB		= lib/libglew32.a lib/libglfw3.a -lgdi32 -lopengl32

.DEFAULT: all

all: $(O_FILES)
	$(CC) $^ -o $(OUT) $(LIB)

build/%.o: src/%.cpp
	$(CC) $(INCLUDE) -D GLEW_STATIC -c $^ -o $@ 
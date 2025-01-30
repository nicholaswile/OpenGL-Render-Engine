CXX := g++
CXX_FLAGS := -std=c++17 -Wall

SDL2_INC := C:\libraries\SDL2-devel-2.30.4-mingw\SDL2-2.30.4\i686-w64-mingw32\include\SDL2
SDL2_LIB := C:\libraries\SDL2-devel-2.30.4-mingw\SDL2-2.30.4\i686-w64-mingw32\lib

SDL2_IMG_INC := C:\libraries\SDL2_image-devel-2.8.2-mingw\SDL2_image-2.8.2\i686-w64-mingw32\include\SDL2
SDL2_IMG_LIB := C:\libraries\SDL2_image-devel-2.8.2-mingw\SDL2_image-2.8.2\i686-w64-mingw32\lib

GLAD_INC := C:\libraries\glad\include
GLAD_SRC := C:\libraries\glad\src

STBI_INC := C:\libraries\stbi 
GLM_INC := C:\libraries\glm-0.9.8.5\glm

SDL_I := -I $(SDL2_INC) -I $(SDL2_IMG_INC)
OPENGL_I := -I $(GLAD_INC) -I $(STBI_INC) -I $(GLM_INC)

SDL_L := -L $(SDL2_LIB) -L $(SDL2_IMG_LIB)
OPENGL_L := -L $(OPENGL_LIB)

LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lOpenGL32
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(GLAD_SRC)/glad.c

all:
	$(CXX) $(CXX_FLAGS) $(SDL_I) $(OPENGL_I) $(SDL_L) -o main $(SRCS) $(LIBS)
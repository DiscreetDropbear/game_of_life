#OBJS specifies which files to compile as part of the project 
OBJS =  src/matrix.cpp src/graphics.cpp src/main.cpp

#CC specifies which compiler we're using 
CC = clang++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -std=c++14

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our executable
OBJ_NAME = conways_game_of_life 

#This is the target that compiles our executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

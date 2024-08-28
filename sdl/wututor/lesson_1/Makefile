#SRC specifies which files to compile as part of the project
SRC = hello.cpp

#OBJ compiled files
OBJ = hello.o

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\Users\action\scoop\apps\msys2\current\ucrt64\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\Users\action\scoop\apps\msys2\current\ucrt64\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -c -g -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ specifies the name of our exectuable
LINK_TARGET = hello.exe

$(LINK_TARGET): $(OBJ)
	$(CC) -o $(LINK_TARGET) $(OBJ) $(LIBRARY_PATHS) $(LINKER_FLAGS)

$(OBJ): $(SRC)
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $(SRC)

clean:
	$(RM) $(LINK_TARGET) hello.o
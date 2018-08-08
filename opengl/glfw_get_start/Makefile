CC = g++
C_FLAGS = -Wall -g 
CL_FLAGS = -lGLEW -lGL -lglfw

OBJ = win.o
OUT = win

$(OUT): $(OBJ)
	$(CC) $(C_FLAGS) -o $(OUT) $(OBJ) $(CL_FLAGS)

clean:
	$(RM) $(OBJ) $(OUT)

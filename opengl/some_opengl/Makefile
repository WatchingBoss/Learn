CC = g++
C_FLAGS = -Wall -g
CL_FLAGS = -lGL -lGLEW -lglfw

OUT = go
OBJ = win.o

$(OUT): $(OBJ)
	$(CC) $(C_FLAGS) -o $(OUT) $(OBJ) $(CL_FLAGS)

clean:
	$(RM) $(OUT) $(OBJ)

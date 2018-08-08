CC = g++
C_FLAGS = -g -Wall
CL_FLAGS = -lGL -lGLEW -lglfw

OBJ = win.o
OUT = go

$(OUT): $(OBJ)
	$(CC) $(C_FLAGS) -o $(OUT) $(OBJ) $(CL_FLAGS)

clean:
	$(RM) $(OBJ) $(OUT)

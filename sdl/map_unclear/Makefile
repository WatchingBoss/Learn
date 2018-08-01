CC = gcc
CFLAGS = -g -Wall
CLFLAGS = -lm -lSDL2main -lSDL2

OUT = go
OBJ = main.o

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(CFLAGS) $(OBJ) $(CLFLAGS)

clean:
	$(RM) $(OUT) $(OBJ)

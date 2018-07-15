CC = g++
CFLAGS = -g -Wall
CLFLAGS = -lSDL2main -lSDL2

OBJ = main.o
OUT = go

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ) $(CLFLAGS)

clean:
	$(RM) $(OBJ) $(OUT)

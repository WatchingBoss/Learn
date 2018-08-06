CC = g++
CFLAGS = -g
CLFLAGS = -lSDL2main -lSDL2

OBJ = hello.o
OUT = go

$(OUT): $(OBJ) 
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ) $(CLFLAGS)

clean:
	$(RM) $(OUT) $(OBJ)

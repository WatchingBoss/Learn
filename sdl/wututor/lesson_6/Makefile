CC = g++
CFLAGS = -Wall -g -std=c++11
CLFLAGS = -lSDL2main -lSDL2 -lSDL2_ttf

OUT = go
OBJ = main.o

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ) $(CLFLAGS)

clean:
	$(RM) $(OBJ) $(OUT)

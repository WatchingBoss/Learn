CC = gcc
CLFLAGS = -lpcap
CFLAGS = -g -Wall

OBJ = scanner.o
HDR = scanner.h inc.h
GO = go

$(GO): $(OBJ) $(HDR)
	$(CC) $(CFLAGS) -o $(GO) $(OBJ) $(CLFLAGS)

clean:
	$(RM) $(GO) $(OBJ)

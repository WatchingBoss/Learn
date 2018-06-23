CC = gcc
CLFLAGS = -lpcap

OBJ = scanner.o
HDR = scanner.h inc.h
GO = go

$(GO): $(OBJ) $(HDR)
	$(CC) -o $(GO) $(OBJ) $(CLFLAGS)

clean:
	$(RM) $(GO) $(OBJ)

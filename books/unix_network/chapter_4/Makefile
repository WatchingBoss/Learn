CC = gcc

OBJ_S = time_server.o
OBJ_C = time_client.o
SER = server
CLI = client
OUT = go

$(OUT): $(OBJ_S) $(OBJ_C)
	$(CC) -o $(SER) $(OBJ_S)
	$(CC) -o $(CLI) $(OBJ_C)

clean:
	$(RM) $(SER) $(CLI) $(OBJ_S) $(OBJ_C)

CC = gcc
CFLAGS = -Wall -Wpedantic -O3

OUT_Q = quick
OUT_QI = quick_insert

OBJ_Q = quick.o
OUT_QI = quick_insert.o

quick: $(OBJ_Q)
	$(CC) $(CFLAGS) -o $(OUT_Q) $(OBJ_Q)

quick: $(OBJ_QI)
	$(CC) $(CFLAGS) -o $(OUT_QI) $(OBJ_QI)

cln:
	$(RM) $(OBJ_Q) $(OBJ_QI) $(OUT_Q) $(OUT_QI)

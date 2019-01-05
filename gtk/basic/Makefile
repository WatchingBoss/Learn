CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra

CF_INC = `pkg-config --cflags gtk+-3.0`
CF_LINK = `pkg-config --libs gtk+-3.0`

SRC = 2.c
OUT = sample

$(OUT):
	$(CC) $(CFLAGS) $(CF_INC) -o $(OUT) $(SRC) $(CF_LINK)

clean:
	$(RM) *.o $(OUT)

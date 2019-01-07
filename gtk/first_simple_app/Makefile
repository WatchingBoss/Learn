CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra

PKGCONFIG = $(shell which pkg-config)
CF_INC = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
CF_LINK = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = app.c example_app.c example_app_win.c
OBJ = $(SRC:.c=.o)
OUT = app

%.o: %.c
	$(CC) $(CFLAGS) $(CF_INC) -c -o $(@F) $<

$(OUT): $(OBJ)
	$(CC) -o $(@F) $(OBJ) $(CF_LINK)

clean:
	$(RM) $(OBJ) $(OUT)

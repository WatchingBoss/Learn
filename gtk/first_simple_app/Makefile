CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -ggdb

PKGCONFIG = $(shell which pkg-config)
CF_INC = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
CF_LINK = $(shell $(PKGCONFIG) --libs gtk+-3.0)
GLIB_COMPILE_RESOURCES = $(shell $(PGKCONFIG) --variable=glib-compile-resources)

SRC = app.c \
example_app.c \
example_app_win.c

RESOURCES = resources.c

OBJ = $(SRC:.c=.o)
OUT = app

$(RESOURCES): example_app.gresource.xml app_xml.glade
	$(GLIB_COMPILE_RESOURCES) example_app.gresource.xml --target=$@ --sourcedir=. \
--generate-source

%.o: %.c
	$(CC) $(CFLAGS) $(CF_INC) -c -o $(@F) $<

$(OUT): $(OBJ)
	$(CC) -o $(@F) $(OBJ) $(CF_LINK)

clean:
	$(RM) $(RESOURCES) $(OBJ) $(OUT)

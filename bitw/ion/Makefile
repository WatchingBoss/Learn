CC      = gcc
CLFLAGS = -lm
VERSION = -std=gnu99
CFLAGS  = -g

TARGET  = go

OBJECT  = ion.o common.o lex.o

$(TARGET): $(OBJECT)
	$(CC) $(VERSION) $(CFLAGS) -o $(TARGET) $(OBJECT) $(CLFLAGS)

clean:
	$(RM) $(TARGET) $(OBJECT)

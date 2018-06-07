CC="gcc"

go: ion.o
	$(CC) -g -o go ion.o

ion.o: ion.c
	$(CC) -g -c ion.c

clean:
	rm go *.o

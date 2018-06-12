CC="gcc"
#CCFLAGS=""
VERSION="-std=gnu99"

go: ion.o
	$(CC) $(VERSION) -g -o go ion.o

ion.o: ion.c
	$(CC) $(VERSION) -g -c ion.c

clean:
	rm go *.o

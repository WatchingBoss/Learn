CC = gcc
CFLAGS = -g -Wall

R = receiver
S = sender

OBJR = receiver.o
OBJS = sender.o

go: $(OBJR) $(OBJS)
	$(CC) $(CFLAGS) -o $(R) $(OBJR)
	$(CC) $(CFLAGS) -o $(S) $(OBJS)

clean:
	$(RM) $(R) $(S) $(OBJR) $(OBJS)

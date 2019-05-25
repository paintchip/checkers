TARGET=checkers
CC=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
PTHREAD=-pthread
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe
LD=g++
LDFLAGS=$(PTHREAD) -export-dynamic
OBJS= checkers.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
 
checkers.o: src/checkers.cpp
	$(CC) -c $(CCFLAGS) src/checkers.cpp -o checkers.o
 
clean:
	rm -f *.o


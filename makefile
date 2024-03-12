.PHONY: all clean

CC = gcc
CFLAGS = -Wall -g
TARGET = digitcompress
OBJS = compress.o encodemain.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c compress.c

encodemain.o: encodemain.c compress.h
	$(CC) $(CFLAGS) -c encodemain.c

clean:
	rm -f $(TARGET) $(OBJS)

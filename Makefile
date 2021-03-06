#Partially sourced From Joey Adams_Stack Overflow

TARGET = prog
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -Werror -std=c11

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f *.gch
	-rm -f $(TARGET)

run:
	./prog
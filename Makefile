SRCS=main.c shell.c io.c
EXECUTABLE=shell
CC=gcc
CFLAGS=-ggdb3 -Wall -std=gnu99

OBJS=$(SRCS:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJS)

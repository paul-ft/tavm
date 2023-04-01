CC=gcc
CFLAGS=-W -Wall -Werror -c -ansi
LDFLAGS=
EXEC=tavm
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o);

all:$(EXEC)

%.o : %c
	$(CC) $^ $(CFLAGS) -o $@

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -rf *.o $(EXEC)

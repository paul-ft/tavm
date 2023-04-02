CC=gcc
CFLAGS=-W -Wall -Werror -c -std=gnu99 -pedantic -g
LDFLAGS=
EXEC=tavm
SRC=$(shell find ./ -type f -name '*.c')
OBJ=$(SRC:.c=.o);

all:$(EXEC)

%.o : %c
	$(CC) $^ $(CFLAGS) -o $@

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -rf *.o $(EXEC)

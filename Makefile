CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include

SRC = src/arena.c
OBJ = $(SRC:.c=.o)

libarena.a: $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) libarena.a

.PHONY: clean

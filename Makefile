# Makefile pour le projet

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS =

SRC = main.c \
      affichage.c \
      check.c \
      selection_1.c \
      selection_vs_ordi.c \
      techniques_1.c \
      JvO_facile.c \
      combat_1.c

OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

.PHONY: all clean

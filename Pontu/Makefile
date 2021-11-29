CC=gcc
CFLAGS=-Wall -Wextra -std=c17 -pedantic
LDFLAGS= $(sdl2-config --cflags --libs)
INCFLAGS= -I include
EXEC=bin/pontu
SRC= $(wildcard src/modele/*.c) $(wildcard src/moteur/*.c) $(wildcard src/vue/*.c) src/main.c


OBJ= $(SRC:.c=.o)

help:
	echo "Usage :"


all: $(EXEC)
	echo $(OBJ)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(INCFLAGS) $(CFLAGS) -o $@ -c $<

.PHONY: clean hardclean 

clean:
	rm -rf *.o

hardclean: clean
	rm -rf $(EXEC)

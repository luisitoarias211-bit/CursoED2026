CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g
SRC = src/main.c src/destino.c src/pasajero.c src/viaje.c src/estadisticas.c
OBJ = $(SRC:.c=.o)
BIN = terminal_buenaventura

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
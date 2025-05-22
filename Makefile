
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Files
SRC = main.c game.c map.c utils.c
OBJ = $(SRC:.c=.o)
DEPS = game.h map.h utils.h

# Output
TARGET = minesweeper

# Default 
all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o $(TARGET)


.PHONY: all clean

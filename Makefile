CC=gcc
CFLAGS=-Werror -Wvla -Wextra 
LDLIBS=-lncurses

SRC_FILES=bird.c game.c pipe.c logic.c
SRC=$(addprefix src/, $(SRC_FILES))
OBJ=$(SRC:.c=.o)
BIN=termbird

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

static: LDFLAGS = -static
static: LDLIBS += -ltinfo
static: $(BIN)

debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -g -fsanitize=address
debug: $(BIN)


clean:
	$(RM) $(OBJ) $(BIN)

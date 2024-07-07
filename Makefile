SRC=./src
BUILD=./build

SRCS=$(wildcard $(SRC)/*.c)
OBJ=$(SRCS:$(SRC)/%.c=$(BUILD)/%.o)

INCLUDE=$(SRC)/include

LDFLAGS=-lm -lc
IFLAGS=-I $(INCLUDE)
CFLAGS=--std=gnu11 \
	   -Werror \
	   -Wall \
	   -Wshadow \
	   -Wextra \
	   -Wmissing-prototypes \
	   -Wold-style-definition \
	   -Wredundant-decls \
	   -O3

default: main

main: $(OBJ)
	gcc $(IFLAGS) $(LDFLAGS) -o $@ $^ $(CFLAGS) 

$(OBJ): $(BUILD)/%.o: $(SRC)/%.c
	gcc $(IFLAGS) $(LDFLAGS) -o $@ -c $< $(CFLAGS) 

info:
	$(info $(SRCS))
	$(info $(OBJ))

clean:
	rm -r $(BUILD)/*

.PHONY: info clean


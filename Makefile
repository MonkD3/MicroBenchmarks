CC=gcc

SRC=./src
TEST=./tests
BUILD=./build

NAME=bench
TNAME=unittest
LIBNAME=lib$(NAME)

# Sources
SRCS=$(wildcard $(SRC)/*.c)
OBJ=$(SRCS:$(SRC)/%.c=$(BUILD)/%.o)

# Test sources
TSRCS=$(wildcard $(TEST)/*.c)
TOBJ=$(TSRCS:$(TEST)/%.c=$(BUILD)/%.o)

INCLUDE=$(SRC)/include

LDFLAGS=-lm -lc
IFLAGS=-I $(INCLUDE)
CFLAGS=--std=gnu11 \
	   -Werror -Wall -Wshadow -Wextra \
	   -Wmissing-prototypes -Wold-style-definition \
	   -Wredundant-decls \

ifeq ($(MODE),dev)
	CFLAGS += -Og -g -fsanitize=address 
else ifeq ($(MODE),release)
	CFLAGS += -O3 \
              -march=native \
              -mtune=generic \
              -DNDEBUG
else 
	CFLAGS += -O2
endif

default: $(LIBNAME).so $(TNAME)

dev:
	MODE=dev $(MAKE)

release:
	MODE=release $(MAKE)

$(LIBNAME).so: $(OBJ)
	$(CC) -shared -fPIC $(IFLAGS) $(LDFLAGS) -o $@ $^ $(CFLAGS) 

$(OBJ): $(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(IFLAGS) $(LDFLAGS) -o $@ -c $< $(CFLAGS) -MMD

$(TNAME): $(TOBJ)
	$(CC) $(IFLAGS) -o $@ $^ $(CFLAGS) $(LDFLAGS) -lcunit -L . -l$(NAME) -Wl,-rpath,.

$(TOBJ): $(BUILD)/%.o: $(TEST)/%.c
	$(CC) $(IFLAGS) -o $@ -c $< $(CFLAGS) $(LDFLAGS) -lcunit -L . -l$(NAME) -Wl,-rpath,.

info:
	$(info $(SRCS))
	$(info $(OBJ))
	$(info $(TOBJ))

clean:
	rm -r $(BUILD)/* $(LIBNAME).so $(TNAME)

.PHONY: info clean


CC:=gcc
LD:=gcc

CFLAGS:=-g -Wall -Wextra -std=c17 -O2
LDFLAGS:= -lpthread -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lm

OBJ:=obj
SRC:=src
BIN:=bin

DIRS:=$(shell find src/ -type d)
BUILD_DIRS:=$(patsubst $(SRC)/%, $(OBJ)/%, $(DIRS))


SRCS:=$(shell find src -name *.c)
OBJS:=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TARGET:= $(BIN)/NEAT



.PHONY: all clean dirs run

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@



dirs:
		for i in $(BUILD_DIRS) ; do \
			mkdir $$i ; \
		done
		mkdir $(BIN) 

clean:
	rm -rf bin
	rm -rf obj

run:
	./$(TARGET)

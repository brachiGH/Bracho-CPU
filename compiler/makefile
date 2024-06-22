CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pedantic -Wno-implicit-function-declaration -g
SRCS = src/assembler/assembler.c src/Opcodes.c src/utilites.c
OBJS = $(SRCS:.c=.o)
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up $(OBJS) $(EXEC)"
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean


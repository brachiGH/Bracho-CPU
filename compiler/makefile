CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pedantic -Wno-implicit-function-declaration -g
SRCS = src/assembler/assembler.c src/Opcodes.c src/utilites.c
OBJS = $(SRCS:.c=.o)
EXEC = assembler

ifeq ($(p),assembler)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up $(OBJS) $(EXEC)"
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean

else

all:
	@echo "Error: Invalid project specified. Please specify 'p=assembler' to build assembler."

clean:
	@echo "Nothing to clean."

.PHONY: all clean

endif

CC = gcc
CCWEB = emcc
CFLAGS = -Iinclude -Wall -Wextra -pedantic -Wno-implicit-function-declaration -g
WEBFLAGS = -s EXPORTED_FUNCTIONS='["_webmain"]' -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -Wnewline-eof
SRCS = src/assembler/assembler.c src/Opcodes.c src/utilites.c
OBJS = $(SRCS:.c=.o)
EXEC = assembler
EXECWEBJS = ../Bracho-emulator/src/js/assembler.js
EXECWEBWASM = ../Bracho-emulator/src/js/assembler.wasm


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
ifeq ($(p),webassembler)

all: $(EXECWEBJS)

$(EXECWEBJS): $(OBJS)
	$(CCWEB) $(OBJS) -o $@ $(WEBFLAGS)

%.o: %.c
	$(CCWEB) $(CFLAGS) -Wnewline-eof -c $< -o $@

clean:
	@echo "Cleaning up $(OBJS) $(EXECWEBWASM)"
	rm -f $(OBJS)  $(EXECWEBJS) $(EXECWEBWASM)

.PHONY: all clean

else

all:
	@echo "Error: Invalid project specified. Please specify 'p=assembler' to build assembler."

clean:
	@echo "Nothing to clean."

.PHONY: all clean

endif
endif
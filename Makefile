CC      ?= gcc
CFLAGS  := -std=c99 -Wall -Wextra -Werror -O0 -g -Isrc -Itest
SRCS    := src/ring_buffer.c test/test_ring_buffer.c
BIN     := build/test_ring_buffer

.PHONY: all test clean

all: test

$(BIN): $(SRCS) src/ring_buffer.h test/unit_test.h
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRCS) -o $@

test: $(BIN)
	./$(BIN)

clean:
	rm -rf build

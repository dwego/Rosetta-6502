CC = clang
CFLAGS = -Iinclude -Isrc/utils -Wall -Wextra -g

LDFLAGS = -lncurses

SRCS := $(shell find . -name '*.c' -not -path './tests/*' -not -path './libs/*')
OBJS := $(SRCS:%=build/%.o)

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

build/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(EXEC)


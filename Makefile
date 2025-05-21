CC = clang
CFLAGS = -Iinclude -Wall -Wextra -g

SRCS := $(shell find . -name '*.c')
OBJS := $(SRCS:%=build/%.o)

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

build/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(EXEC)


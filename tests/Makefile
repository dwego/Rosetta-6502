CC = clang
CFLAGS = -I../include -I./include -I../libs/unity/src -Wall -Wextra -g

SRCS := $(filter-out ../src/main.c, $(shell find ../src ../include -name '*.c'))

UNITY_SRC := ../libs/unity/src/unity.c

TEST_SRCS := $(shell find . \( -path './instruction_tests*' -prune \) -o -name '*.c' -print)

ALL_SRCS := $(SRCS) $(UNITY_SRC) $(TEST_SRCS)


OBJS := $(ALL_SRCS:../%=%)
OBJS := $(OBJS:./%=tests/%)
OBJS := $(OBJS:%=build/%.o)

EXEC = test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

build/%.c.o: ../%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/tests/%.c.o: tests/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/libs/unity/src/%.c.o: ../libs/unity/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(EXEC)


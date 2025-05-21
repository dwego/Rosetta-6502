CC = clang
CFLAGS = -Iinclude -Wall -Wextra -g

SRCS := $(shell find . -name '*.c')
OBJS := $(SRCS:.c=.o)
EXEC = programa

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)


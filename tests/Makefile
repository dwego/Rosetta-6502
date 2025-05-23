CC = clang
CFLAGS = -I../include -I./include -I../libs/unity/Unity/src -Wall -Wextra -g

# Arquivos fonte principais (src + include), exceto main.c
SRCS := $(filter-out ../src/main.c, $(shell find ../src ../include -name '*.c'))

# Unity source
UNITY_SRC := ../libs/unity/Unity/src/unity.c

# Arquivos de testes recursivos (tudo que for .c dentro de ./tests)
TEST_SRCS := $(shell find . -name '*.c')

# Todos os fontes compilados
ALL_SRCS := $(SRCS) $(UNITY_SRC) $(TEST_SRCS)

# Objetos na pasta build, mantendo a estrutura (removendo ../)
OBJS := $(ALL_SRCS:../%=%)
OBJS := $(OBJS:./%=tests/%)
OBJS := $(OBJS:%=build/%.o)

EXEC = test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# Regra genérica para compilar qualquer .c encontrado
build/%.c.o: ../%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/tests/%.c.o: tests/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/libs/unity/Unity/src/%.c.o: ../libs/unity/Unity/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(EXEC)


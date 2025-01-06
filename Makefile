CC = gcc
CFLAGS = -Wall -Wextra -I./src
LDFLAGS = -ljson-c

ifeq ($(OS),Windows_NT)
	EXECUTABLE = agent.exe
	RM = del /Q
else
	EXECUTABLE = agent
	RM = rm -f
endif

SRCS = src/main.c src/agent.c src/lux/kit.c src/lux/utils.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(EXECUTABLE)

test: $(EXECUTABLE)
	./test/test_agent.c 
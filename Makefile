CC = clang
CFLAGS = -Wall -g
LDLIBS = -lncurses
FRAMEWORKS = -framework Foundation -framework AppKit

SRCS_C = main.c interface.c reader.c str.c
SRCS_M = writer.m

OBJS_C = $(SRCS_C:.c=.o)
OBJS_M = $(SRCS_M:.m=.o)

TARGET = hisi

.PHONY: all build clean run install uninstall

all: build

build: $(TARGET)

$(TARGET): $(OBJS_C) $(OBJS_M)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) $(FRAMEWORKS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.m
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(TARGET)

clean:
	rm -f $(OBJS_C) $(OBJS_M) $(TARGET)

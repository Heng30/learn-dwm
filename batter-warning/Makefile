TARGET := battery-warning
ROOT_DIR := $(shell pwd)

CC := gcc
LD := gcc

CCFLAGS := -g -Os -W -Wall
GTKLIB := `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS := $(GTKLIB) -export-dynamic

SRCS := ${wildcard *.c}
OBJS := ${patsubst %.c, %.o, $(SRCS)}

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) -c ${CCFLAGS} -o $@  $< $(GTKLIB)

install: all
	cp $(TARGET) ~/bin

clean:
	rm -f *.o $(TARGET)

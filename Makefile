CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -O2
SRC     = $(wildcard src/*.c)
TARGET  = snake

ifeq ($(OS),Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET := $(TARGET).exe
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME),Darwin)
        LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    else
        LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f snake snake.exe

.PHONY: all run clean

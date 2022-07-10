

TARGET = main

CC = gcc

BUILD_DIR := build
SOURCE_DIR := src

SRCS = $(shell find $(SOURCE_DIR)/ -type f -name '*.c')
OBJS = $(SRCS:$(SOURCE_DIR)/%=$(BUILD_DIR)/%.o)

INCLUDE_DIR := include
INCLUDES := -I $(INCLUDE_DIR)
WARNINGS := -Wall -Wpedantic

CFLAGS := $(INCLUDES)
CFLAGS += $(WARNINGS)
CFLAGS += -g
LDFLAGS = -lmenu -lpanel -lform -lncurses

all: $(BUILD_DIR)/$(TARGET)

run: all
	@$(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.c.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -ri $(BUILD_DIR)




# gcc -I include -Wall -Wpedantic -g -c src/main.c -o build/main.c.o
# gcc -I include -Wall -Wpedantic -g -lmenu -lpanel -lform -lncurses build/form_functions.c.o build/main.c.o -o build/main

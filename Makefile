# CC :=gcc
# LDFLAGS :=-lncurses -lmenu -lform -lpanel
# C_SOURCES :=$(wildcard *.c)
# C_OBJS :=$(C_SOURCES:.c=.o)
#
# #
# # all:$(C_EXECUTABLE) $(CPP_EXECUTABLE)
# #
# # $(C_EXECUTABLE):$(C_SOURCES)
# # 	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@
# #
# # $(CPP_EXECUTABLE):$(CPP_SOURCES)
# # 	$(CPP) $< $(LDFLAGS) $(CFLAGS) -o $@
# #
# # clean:
# # 	rm -rf $(EXECUTABLE)
#
# TARGET = main
# BUILD_DIR := build
#
# all:$(TARGET)
#
# $(BUILD_DIR)/%.o: %.c
# 	mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@
#
# $(TARGET):$(BUILD_DIR)/$(C_OBJS)
# 	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(TARGET)
#



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

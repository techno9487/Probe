SRC = $(wildcard *.c)
ROOT = ../
BUILD_DIR = $(ROOT)/build
OBJ = $(SRC:%.c=$(BUILD_DIR)/$(EXEC)_%.o)
EXEC = probe
OUTPUT = $(BUILD_DIR)/$(EXEC)

CFLAGS += -Wall -O2 -g

all: $(OUTPUT)

debug: $(OUTPUT)_dbg

$(OUTPUT): $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) 

$(OUTPUT)_dbg: $(OBJ)
	gcc -g -o $@ $^ $(LDFLAGS)

$(OUTPUT)_%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OUTPUT)_*.o
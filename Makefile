SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=build/%.o)

EXEC = probe
CFLAGS += -Wall -O2 -g

all: $(EXEC)

debug: $(EXEC)_dbg

$(EXEC): $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) 

$(EXEC)_dbg: $(OBJ)
	gcc -g -o $@ $^ $(LDFLAGS)

build/%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o
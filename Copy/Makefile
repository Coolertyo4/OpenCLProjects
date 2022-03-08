CC=clang
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -g
SRC=main.o log.o
OUT=app
FRAMEWORK=-framework OpenCL

all: $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(OBJ) $(FRAMEWORK)
	rm -rf *.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

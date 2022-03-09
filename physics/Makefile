CC=clang
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -DGPU -g
SRC=main.o
OUT=-o physics
FRAMEWORK=-framework OpenCL
LIBS=-llog

all: $(SRC)
	$(CC) $(CFLAGS) $(OUT) $(SRC) $(OBJ) $(LIBS) $(FRAMEWORK)
	rm -rf *.o
clean:
	rm -rf *.o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

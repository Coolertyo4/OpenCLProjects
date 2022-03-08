CC=clang
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -DGPU -g
SRC=main.o log.o gpu.o cpu.o timing.o args.o
OUT=app
FRAMEWORK=-framework OpenCL

all: $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(OBJ) $(FRAMEWORK)
	rm -rf *.o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

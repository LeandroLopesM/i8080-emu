CC=gcc
CFLAGS=-Wall -Wextra

test.exe: test.c cpu/cpu.o core/core.o
	$(CC) $(CFLAGS) test.c -o test cpu/cpu.o core/core.o

include core/core.mk
include cpu/cpu.mk

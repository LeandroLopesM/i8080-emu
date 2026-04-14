OBJDIR ?= bin/obj
CFLAGS ?= -Wall -Wextra -ggdb

$(OBJDIR)/cli.o: cli/cli.c
	$(CC) cli/cli.c -c -o $(OBJDIR)/cli.o $(CFLAGS)
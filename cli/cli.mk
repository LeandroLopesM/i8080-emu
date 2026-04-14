OBJDIR ?= bin/obj
CFLAGS ?= -Wall -Wextra -ggdb
CLI_DEPS = \
	$(OBJDIR)/interface.o \
	$(OBJDIR)/compiler.o \


$(OBJDIR)/cli.o: $(CLI_DEPS)
	ld --relocatable $(CLI_DEPS) -o $(OBJDIR)/cli.o

$(OBJDIR)/interface.o: cli/cli.c
	$(CC) cli/cli.c -c -o $(OBJDIR)/interface.o $(CFLAGS)

CC_DIR=cli/external/i8080-cc/compiler
include cli/external/i8080-cc/compiler/compiler.mk
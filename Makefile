CC=gcc
CFLAGS ?= -Wall -Wextra

BINDIR=bin
OBJDIR=$(BINDIR)/obj

EMU_DEPS = 					\
	emu.c					\
	$(OBJDIR)/core.o		\
	$(OBJDIR)/cpu.o			\
	$(OBJDIR)/cli.o

$(BINDIR)/emu: $(OBJDIR) $(EMU_DEPS)
	$(CC) $(EMU_DEPS) -o $(BINDIR)/emu $(CFLAGS)

ifdef DEBUG
CFLAGS+=-ggdb -DDEBUG=1
VERBOSE=1
endif
ifdef VERBOSE
CFLAGS+=-DVERBOSE=1
endif

include cli/cli.mk
include cpu/cpu.mk
include core/core.mk

$(OBJDIR):
	mkdir -p $(OBJDIR)
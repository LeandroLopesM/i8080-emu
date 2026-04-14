CC=gcc
CFLAGS+= -Wall -Wextra

BINDIR=bin
OBJDIR=$(BINDIR)/obj

$(BINDIR)/emu: emu.c $(OBJDIR)/core.o $(OBJDIR)/cpu.o
	$(CC) emu.c $(OBJDIR)/core.o $(OBJDIR)/cpu.o -o $(BINDIR)/emu $(CFLAGS)

include cpu/cpu.mk
include core/core.mk

$(BINDIR):
	mkdir $(BINDIR)
$(OBJDIR): $(BINDIR)
	mkdir -p $(OBJDIR)
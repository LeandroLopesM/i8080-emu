CC=gcc
CFLAGS+= -Wall -Wextra

BINDIR=bin
OBJDIR=$(BINDIR)/obj

include cpu/cpu.mk
include core/core.mk

$(BINDIR):
	mkdir $(BINDIR)
$(OBJDIR): $(BINDIR)
	mkdir -p $(OBJDIR)
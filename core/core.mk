DIR=core
CORE_DEPS = 		\
	$(OBJDIR)/log.o	\
	$(OBJDIR)/calc.o	\

$(OBJDIR)/core.o: $(OBJDIR) $(CORE_DEPS)
	ld --relocatable $(CORE_DEPS) -o $(OBJDIR)/core.o

$(OBJDIR)/log.o: $(DIR)/log.c
	$(CC) $(DIR)/log.c -c -o $(OBJDIR)/log.o $(CFLAGS)

$(OBJDIR)/calc.o: $(DIR)/calc.c
	$(CC) $(DIR)/calc.c -c -o $(OBJDIR)/calc.o $(CFLAGS)
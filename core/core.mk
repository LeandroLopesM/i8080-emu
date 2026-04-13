DIR=core
CORE_SOURCES = 		\
	$(OBJDIR)/log.o	\
	$(OBJDIR)/calc.o	\

$(OBJDIR)/core.o: $(OBJDIR) $(CORE_SOURCES) $(OBJDIR)
	ld --relocatable $(CORE_SOURCES) -o $(OBJDIR)/core.o

$(OBJDIR)/log.o: $(DIR)/log.c $(OBJDIR)
	$(CC) $(DIR)/log.c -c -o $(OBJDIR)/log.o $(CFLAGS)
$(OBJDIR)/calc.o: $(DIR)/calc.c $(OBJDIR)
	$(CC) $(DIR)/calc.c -c -o $(OBJDIR)/calc.o $(CFLAGS)
SOURCES = 				\
	$(OBJDIR)/resolve.o	\
	$(OBJDIR)debug.o	\
	$(OBJDIR)/decode.o	\
	$(OBJDIR)/exec.o	\

cpu/cpu.o: $(SOURCES) $(OBJDIR)
	ld $(SOURCES) --relocatable -o $(OBJDIR)/cpu.o

$(OBJDIR)/resolve.o: cpu/decode/resolve.c $(OBJDIR)
	$(CC) cpu/decode/resolve.c -c -o $(OBJDIR)/resolve.o $(CFLAGS)
$(OBJDIR)debug.o: cpu/debug/debug.c $(OBJDIR)
	$(CC) cpu/debug/debug.c -c -o $(OBJDIR)debug.o $(CFLAGS)
$(OBJDIR)/decode.o: cpu/decode/decode.c $(OBJDIR)
	$(CC) cpu/decode/decode.c -c -o $(OBJDIR)/decode.o $(CFLAGS)
$(OBJDIR)/exec.o: cpu/exec.c $(OBJDIR)
	$(CC) cpu/exec.c -c -o $(OBJDIR)/exec.o  $(CFLAGS) -Wno-implicit-fallthrough
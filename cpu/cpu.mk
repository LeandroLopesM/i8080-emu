CPU_SOURCES = 	\
	cpu/decode/resolve.o	\
	cpu/debug/debug.o		\
	cpu/decode/decode.o		\
	cpu/exec.o				\

cpu/cpu.o: $(CPU_SOURCES)
	ld $(CPU_SOURCES) --relocatable -o cpu/cpu.o

cpu/decode/resolve.o: cpu/decode/resolve.c
	$(CC) cpu/decode/resolve.c -c -o cpu/decode/resolve.o $(CFLAGS)
cpu/debug/debug.o: cpu/debug/debug.c
	$(CC) cpu/debug/debug.c -c -o cpu/debug/debug.o $(CFLAGS)
cpu/decode/decode.o: cpu/decode/decode.c
	$(CC) cpu/decode/decode.c -c -o cpu/decode/decode.o $(CFLAGS)
cpu/exec.o: cpu/exec.c
	$(CC) cpu/exec.c -c -o cpu/exec.o  $(CFLAGS) -Wno-implicit-fallthrough
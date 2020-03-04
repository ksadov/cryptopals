CC=gcc
CFLAGS=-Werror
DEPS = cputils.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cp1: cp1.o cputils.o
	@$(CC) $(CFLAGS) -o cp1.exe cp1.o cputils.o
	@./cp1.exe

cp2: cp2.o cputils.o
	@$(CC) $(CFLAGS) -o cp2.exe cp2.o cputils.o
	@./cp2.exe

cp3: cp3.o cputils.o
	@$(CC) $(CFLAGS) -o cp3.exe cp3.o cputils.o
	@./cp3.exe

cp4: cp4.o cputils.o
	@$(CC) $(CFLAGS) -o cp4.exe cp4.o cputils.o
	@./cp4.exe

cp5: cp5.o cputils.o
	@$(CC) $(CFLAGS) -o cp5.exe cp5.o cputils.o
	@./cp5.exe

cp6: cp6.o cputils.o
	@$(CC) $(CFLAGS) -o cp6.exe cp6.o cputils.o
	@./cp6.exe

clean:
	rm -f *.exe
	rm -f *.o

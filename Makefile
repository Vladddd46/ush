CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
all: install clean
install:
	cp src/*/*.c .
	cp src/*/*/*.c .
	cp src/*/*/*/*.c .
	cp inc/*.h . 
	$(CC) $(CFLAGS) *.c -o ush
uninstall: clean
	rm ush
clean:
	rm *.c
	rm *.h
reinstall: uninstall install
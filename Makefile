NAME = ush	
CFLGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install clean

install:
	make -C libmx -f Makefile install
	cp src/*/*.c .
	cp src/*/*/*.c .
	cp src/*/*/*/*.c .
	cp inc/*.h .
	clang $(CFLGS) -c  *.c
	mkdir -p obj
	mv *.o ./obj
	clang $(CFLGS) ./obj/*.o libmx/libmx.a -o $(NAME)

clean:
	make -C libmx -f Makefile
	rm -rf ./obj/*.o *.c ./*.h
	rm -rf ./obj
uninstall:
	rm  ush
	rm  libmx/libmx.a
reinstall: uninstall install
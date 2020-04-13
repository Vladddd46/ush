all:
	cp src/*/*.c .
	cp src/*/*/*.c .
	cp src/*/*/*/*.c .
#	cp src/*/*/*/*/*.c .
	cp inc/*.h . 
	clang -std=c11 -Wall -Wextra -Wpedantic -Werror *.c -o ush
	rm *.c
	rm *.h

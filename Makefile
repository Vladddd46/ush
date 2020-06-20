NAME	=	ush

CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g


all:
	make -sC ./libmx
	clang -I inc/ src/*/*.c src/*/*/*.c src/*/*/*/*.c libmx/libmx.a -o $(NAME)

clean:
	rm -rf libmx/libmx.a
	rm -rf libmx/obj
	rm -rf ush
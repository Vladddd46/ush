CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
NAME = libmx.a
HEADTMP = ./libmx.h
INC = ./inc/*.h
SRC = ./*.c
SRCS = ./src/*.c
OBJ = ./*.o

all: install clean
install:
	@cp $(INC) $(SRCS) .
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar -rc $(NAME) $(OBJ)
uninstall:
	@rm -rf $(NAME)
clean:
	@rm -rf $(OBJ) $(SRC) $(HEADTMP)
reinstall: clean all
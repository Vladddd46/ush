#include "ush.h"

/*
    * getting user`s input depenting on tty
*/
char *mx_getting_input() {
    char *input;
    size_t size;

    if (isatty(0)) {
        write(1, "u$h> ", 5);
        input = mx_input();
    }
    else {
        size = 100;
        input = mx_strnew(size);
        getline(&input, &size, stdin);
        input[strlen(input) - 1] = '\0';
    }
    return input;
}




#include "ush.h"


// Getting user`s input depenting on tty
char *mx_getting_input() {
    char *input;
    size_t size;
    // Save orig. terminal settings.need for input in ncanonical mode.
    struct termios orig_termios;
    tcgetattr(0, &orig_termios);

    if (isatty(0)) {
        write(1, "u$h> ", 5);
        input = mx_input(orig_termios);
    }
    else {
        size = 100;
        input = mx_strnew(size);
        getline(&input, &size, stdin);
        input[strlen(input) - 1] = '\0';
    }
    return input;
}




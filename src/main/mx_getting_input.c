#include "ush.h"


// Getting user`s input depenting on tty
char *mx_getting_input(t_local_env **local_env) {
    char *input;
    size_t size;
    char *promt;
    // Save orig. terminal settings.need for input in ncanonical mode.
    struct termios orig_termios;
    tcgetattr(0, &orig_termios);

    if (isatty(0)) {
        promt = mx_get_var_value(local_env, "PROMPT");
        write(1, promt, mx_strlen(promt));
        input = mx_input(orig_termios, local_env);
    }
    else {
        // getline func. reallocates mem if it`s not enough.
        size = 100;
        input = mx_strnew(size);
        getline(&input, &size, stdin);
        input[strlen(input) - 1] = '\0';
    }
    return input;
}




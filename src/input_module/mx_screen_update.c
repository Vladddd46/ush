#include "ush.h"
/*
 * Updates screen view depenging on user`s input.
 * If backspace {delet 1 char}
 * If normal char {print char}
 * If ctrl+char => handle.
*/

// Clears line in terminal window.(fills it with spaces ' ')
static void line_cleaner(char *input) {
    // + 6 because of "u$h> "
    int free_space = mx_strlen(input) + 6;
    write(1, "\r", 1);
    while (free_space) {
        write(1, " ", 1);
        free_space--;
    }
}

static void input_printer(char *input) {
    int len = mx_strlen(input) - 1;
    int i = 0;

    while(i < len) {
        write(1, &input[i], 1);
        i++;
    }
}

void mx_screen_update(char *input, char buff, t_local_env **local_env) {
    char *promt;

    if (buff == 127) {
        line_cleaner(input);
        promt = mx_get_var_value(local_env, "PROMPT");
        write(1, "\r", 1);
        write(1, promt, mx_strlen(promt));
        input_printer(input);
    }
    else if (buff != '\n' && buff != 127)
        write(1, &buff, 1);
}




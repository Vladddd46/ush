#include "ush.h"
/*
    * updates screen view depenging on user`s input.
    * if backspace {delet 1 char}
    * if normal char {print char}
    * if ctrl+char => handle.
*/

// clears line in terminal window.(fills it with spaces ' ')
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

void mx_screen_update(char *input, char buff) {
    if (buff == 127) {
        line_cleaner(input);
        write(1, "\ru$h> ", 7);
        input_printer(input);
    }
    else if (buff != '\n' && buff != 127)
        write(1, &buff, 1);
}




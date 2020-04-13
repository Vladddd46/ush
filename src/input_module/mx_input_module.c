#include "ush.h"
/*
    * user`s input functional
    * reading from stdout is performing
      in non-canonical terminal mode.
*/

// reallocates memory for buffer(input) if it`s needed.
static void reallocation(char **input, int *index, int *size) {
    char *free_input;

    if (*index + 1 == *size) {
        free_input = *input;
        *input = mx_str_realloc(*input, 100);
        *size += 100;
        free(free_input);
     }
}

// decrements writing index, when user wrote backspace(127)
static void index_decrement(int *index, char **input) {
    if (*index != 0)
        *index -= 1;
    input[0][*index] = '\0';
}

// cuts buffer(input) into inputed sting size
static char *buff_cutter(char **input, int *index) {
    char *result;

    input[0][*index - 1] = '\0';
    result = mx_string_copy(input[0]);
    free(input[0]);
    return result;
}

char *mx_input() {
    struct termios orig_termios;
    tcgetattr(0, &orig_termios);
    char buff = '\0';
    int  size = 100;
    char *input = mx_strnew(size);
    int  index = 0;

    while (buff != 13 && buff != 10) {
        mx_enable_raw_mode(orig_termios);
        read(0, &buff, 1);
        mx_screen_update(input, buff, orig_termios);
        if (buff == 127)
            index_decrement(&index, &input);
        else {
            reallocation(&input, &index, &size);
            input[index] = buff;
            index++;
        }
        mx_disable_raw_mode(orig_termios);
    }
    return buff_cutter(&input, &index);
}

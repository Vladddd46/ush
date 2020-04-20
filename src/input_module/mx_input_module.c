#include "ush.h"
/*
    * user`s input functional
    * reading from stdout is performing
      in non-canonical terminal mode.
*/

// cuts buffer(input) into inputed sting size
static char *buff_cutter(char **input, int *index) {
    char *result;

    input[0][*index - 1] = '\0';
    result = mx_string_copy(input[0]);
    free(input[0]);
    return result;
}

static jmp_buf jump;
static void sigint_handler() {
    longjmp(jump, 42);
}

/*
    * does all needed operations, that should be performed
      after inputing characker by user.
      a) updates screen
         - prints new inputed char.
         - in case of backspace erase  char.
         - reallocates buffer if it`s size is full.
*/
static void post_input(char **input, char buff, int *size, int *index) {
    mx_screen_update(input[0], buff);
    if (buff == 127) {
        if (*index != 0) {
            *index -= 1;
            input[0][*index] = '\0';
        }
    }
    else {
        mx_reallocation(input, index, size);
        input[0][*index] = buff;
        *index += 1;
    }
}

char *mx_input(struct termios orig_termios) {
    char buff = '\0';
    int  size = 100;
    char *input = mx_strnew(size);
    int  index = 0;

    while (buff != 13 && buff != 10) {
        signal(SIGINT, sigint_handler);
        mx_enable_raw_mode(orig_termios);
        if (setjmp(jump) == 42) {
              free(input);
              mx_disable_raw_mode(orig_termios);
              return NULL;
         }
        read(0, &buff, 1);
        mx_ctrl_d(buff, orig_termios);
        post_input(&input, buff, &size, &index);
        mx_disable_raw_mode(orig_termios);
    }
    return buff_cutter(&input, &index);
}

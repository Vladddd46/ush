#include "ush.h"

/*
    * exits from ./ush
    * executes when ctrl+d is pressed.
*/
void mx_ctrl_d(struct termios orig_termios) {
    mx_disable_raw_mode(orig_termios);
    printf("\n%s\n", "process exited...");
    exit(0);
}
